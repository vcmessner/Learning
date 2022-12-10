from django.http import JsonResponse
from .models import Drink, MyUser
from .serializer import Myserializer, UserSerializer
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework import status
from rest_framework.views import  APIView   
from rest_framework.exceptions import APIException
from .auth import create_acess_token, create_refresh_token, decode_acess_token, decode_refresh_token, authenticate_token
from rest_framework.authentication import get_authorization_header


class DrinkApiView(APIView):
    def post(self,request):
        id = authenticate_token(request)
        if id!=None:
            serializer = Myserializer(data=request.data)
            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data, status = status.HTTP_201_CREATED)

    def view(self,request): 
        id = authenticate_token(request)
        if id!=None:
            drink = Drink.objects.all()
            serializer = Myserializer(drink,many=True)
            return Response(serializer.data, status = status.HTTP_201_CREATED)

    def delete(self,request):
        id = authenticate_token(request)
        if id!=None:
            try:
                drink=Drink.objects.get(pk=id)
            except:
                return Response(status=status.HTTP_404_NOT_FOUND)
            drink.delete()
            return Response(status = status.HTTP_204_NO_CONTENT)
    

    def put(self,request):
        id = authenticate_token(request)
        if id!=None:
            try:
                drink=Drink.objects.get(pk=id)
            except:
                return Response(status=status.HTTP_404_NOT_FOUND)
            serializer = Myserializer(drink,data=request.data,format=None)
            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data, status = status.HTTP_201_CREATED)
            else:
                return Response(serializer.errors, status = status.HTTP_400_BAD_REQUEST)
    
    
    
    
    def get(self,request):
        id = authenticate_token(request)
        if id!=None:
            try:
                drink=Drink.objects.get(pk=id)
            except:
                return Response(status=status.HTTP_404_NOT_FOUND)
            serializer = Myserializer(drink)
            return Response(serializer.data)


        







class LoginApiView(APIView):
    def post(self,request):
        user = MyUser.objects.filter(username = request.data['username']).first()
        if not user:
            raise APIException('Invalid Credentials')
        #if not user.check_passsword(request.data['password'])
            #raise APIException('Invalid Credentials')
        user = MyUser.objects.filter(username = request.data['password']).first()
        if not user:
            raise APIException('Invalid Credentials')
        #serializer = UserSerializer(user)
        access_token = create_acess_token(user.id)
        print(access_token)
        refresh_token = create_refresh_token(user.id)
        response = Response()
        response.set_cookie(key='refreshToken', value = refresh_token, httponly=True)
        response.data = {'token': access_token}
        #print(access_token)
        return response

class UserAPIView(APIView):

    def view (self,request):
        print("entrei")
        id = authenticate_token(request)
        if id!=None:
            user =MyUser.objects.filter(id=id).first()  
            if(user.admin):
                out_user = MyUser.objects.all()
                serializer = Myserializer(out_user,many=True)
                return Response(serializer.data, status = status.HTTP_201_CREATED)


    def get(self,request):
        id = authenticate_token(request)
        if id!=None:            
            user =MyUser.objects.filter(id=id).first()
            if(user.admin) and (request.data): #prevent exception in case of a          
                if(request.data['a']=='all'): # get all users
                    out_user = MyUser.objects.all()
                    serializer = Myserializer(out_user,many=True)
                    return Response(data={"all users":serializer.data}, status = status.HTTP_201_CREATED)
            return Response(UserSerializer(user).data)
        return Response(status = status.HTTP_400_BAD_REQUEST)
    
    def put(self,request):
        id = authenticate_token(request)
        if id!=None:
            user =MyUser.objects.filter(id=id).first()  
            user.admin=not user.admin          
            user.save()
            print(user.admin)
            return Response(status = status.HTTP_201_CREATED)
        else:
            return Response(status = status.HTTP_400_BAD_REQUEST)


    def delete(self,request):
        id = authenticate_token(request)
        if id!=None:
            user =MyUser.objects.filter(id=id).first()  
            user.delete()
            return Response(status = status.HTTP_201_CREATED)
        else:
            return Response(status = status.HTTP_400_BAD_REQUEST)

    

class RefreshAPIView(APIView):
     def get(self,request):
        token = request.COOKIES.get('refreshToken')
        id = decode_refresh_token(token)
        access_token = create_acess_token(id)
        return Response({'token':access_token})

class LogoutAPIView(APIView):
     def post(self,request):
        response= Response()
        response.delete_cookie(key = 'refreshToken')
        response.data = {'message' : 'Logged out'}
        return response



@api_view(['POST'])
def create_user(request,format=None):
    serializer = UserSerializer(data=request.data)
    if serializer.is_valid():
        serializer.save()
        print(serializer.data)
        return Response(serializer.data,status = status.HTTP_201_CREATED)
    print('5')
    return Response(serializer.errors, status = status.HTTP_400_BAD_REQUEST)