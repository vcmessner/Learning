from django.http import JsonResponse
from pools.models import MyUser,MyTask
from pools.serializer import UserSerializer,TaskSerializer
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework import status
from rest_framework.views import  APIView   
from rest_framework.exceptions import APIException
from .auth import create_acess_token, create_refresh_token, decode_acess_token, decode_refresh_token, authenticate_token, access_duration, refresh_duration, valid_creation_window
from rest_framework.authentication import get_authorization_header
from datetime import datetime, timedelta
from datetime import timezone



class LoginApiView(APIView):
    def post(self,request):
        user = MyUser.objects.filter(username = request.data['username']).first()
        if not user:
            raise APIException('Invalid Credentials')
        if not user.check_password(request.data['password']):
            raise APIException('Invalid Credentials')
        user = MyUser.objects.filter(username = request.data['password']).first()
        if not user:
            raise APIException('Invalid Credentials')
        diff =datetime.now(timezone.utc)-user.last_token_created_at
        print("Refresh Token created " + str(diff.seconds) + " seconds ago")

        if(abs(diff.seconds))>=(refresh_duration-valid_creation_window).seconds:
            access_token = create_acess_token(user.username)
            refresh_token = create_refresh_token(user.username)
            user.last_token_created_at=datetime.now(timezone.utc)
            user.token = refresh_token
            user.save()
            response = Response()
            response.set_cookie(key='refreshToken', value = refresh_token, httponly=True)
            response.data = {'token': access_token}
            return response
        else:
            response = Response()
            response.data = {'Refresh token still valid. Refresh token': user.token}
            return response

class UserAPIView(APIView):

    def get(self,request):
        username = authenticate_token(request)
        if username!=None:         
            user =MyUser.objects.filter(username=username).first()  
            if(user.admin) and (request.data): #prevent exception in case of a            
                if(request.data['a']=='all'): # get all users  
                    out_user = MyUser.objects.all()
                    serializer = UserSerializer(out_user,many=True)
                    return Response(data={"all users":serializer.data}, status = status.HTTP_201_CREATED)
            return Response(UserSerializer(user).data)
        return Response(status = status.HTTP_400_BAD_REQUEST)
    
    def put(self,request):
        username = authenticate_token(request)
        if username!=None:
            user =MyUser.objects.filter(username=username).first()  
            user.admin=not user.admin          
            user.save()
            print(user.admin)
            return Response(status = status.HTTP_201_CREATED)
        else:
            return Response(status = status.HTTP_400_BAD_REQUEST)


    def delete(self,request):
        username = authenticate_token(request)
        if username!=None:
            user =MyUser.objects.filter(username=username).first()  
            user.delete()
            response= Response()
            response.delete_cookie(key = 'refreshToken')
            response.data = {'message' : 'Current User Deleted. Logged out'}
            return response
        else:
            return Response(status = status.HTTP_400_BAD_REQUEST)

    

class RefreshAPIView(APIView):
     def get(self,request):
        token = request.COOKIES.get('refreshToken')
        username = decode_refresh_token(token)
        access_token = create_acess_token(username)
        return Response({'token':access_token})

class LogoutAPIView(APIView):
     def post(self,request):
        response= Response()
        response.delete_cookie(key = 'refreshToken')
        response.data = {'message' : 'Logged out'}
        return response

class CreateUserAPIView(APIView):
     def post(self,request):
        data = request.data
        access_token = create_acess_token(data['username'])
        print (access_token)
        refresh_token = create_refresh_token(data['username'])
        data['last_token_created_at'] = datetime.now(timezone.utc)
        data['token'] = refresh_token
        serializer = UserSerializer(data=data)
        if serializer.is_valid():            
            serializer.save()
            response = Response()
            response.set_cookie(key='refreshToken', value = refresh_token, httponly=True)
            response.data = {'token': access_token, 'User':serializer.data}
            return response
        return Response(serializer.errors, status = status.HTTP_400_BAD_REQUEST)


class TaskApiView(APIView):
    def post(self,request):
        username = authenticate_token(request)
        user =MyUser.objects.filter(username=username).first() 
        if username!=None:
            data = request.data
            data['Foreign_id'] = user.id
            serializer = TaskSerializer(data=request.data)
            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data, status = status.HTTP_201_CREATED)
            

    def get(self,request): 
        username = authenticate_token(request)
        if username!=None:
            task = MyTask.objects.all()
            serializer = TaskSerializer(task,many=True)
            return Response(serializer.data, status = status.HTTP_201_CREATED)

    def delete(self,request):
        username = authenticate_token(request)
        if username!=None:
            try:
                data = request.data
                task=MyTask.objects.get(public_id=data['public_id'])
            except:
                return Response(status=status.HTTP_404_NOT_FOUND)
            task.delete()
            return Response(status = status.HTTP_204_NO_CONTENT)
    

    def put(self,request):
        username = authenticate_token(request)
        data = request.data
        if username!=None:
            try:
                task=MyTask.objects.get(public_id=data['public_id'])
                task.complete = not task.complete
            except:
                return Response(status=status.HTTP_404_NOT_FOUND)
            task.save()
            return Response(status = status.HTTP_201_CREATED)
        else:
            return Response(status = status.HTTP_400_BAD_REQUEST)
    