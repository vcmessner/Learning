from rest_framework import serializers
from .models import Drink,MyUser

class Myserializer(serializers.ModelSerializer):
    class Meta:
        model=Drink
        fields = ['id', 'name']



class UserSerializer(serializers.ModelSerializer):
    class Meta:
        model=MyUser
        fields = ['id', 'public_id' , 'email', 'username', 'password' , 'name' , 'admin', 'token' , 'last_token_created_at']
        extra_kwargs = { 
            'password' : {'write_only':True}
        }


        #def create(self,validated_data):
           # password = validated_data.pop('password',None)
            #instance = self.Meta.model(**validated_data)
           # if password != None:
              #  instance.set_password(password)
          #  instance.save()
           # return instance
#




class TaskSerializer(serializers.ModelSerializer):
    class Meta:
        model=Drink
        fields = ['id', 'name']
