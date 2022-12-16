from rest_framework.serializers import ModelSerializer
from .models import MyUser, MyTask




class UserSerializer(ModelSerializer):
    class Meta:
        model=MyUser
        fields = ['id', 'public_id' , 'email', 'username', 'password' , 'name' , 'admin', 'token' , 'last_token_created_at']
        #extra_kwargs = { 
            #'password' : {'write_only':True}
        #}

    def create(self, validated_data):
        password = validated_data.pop('password')
        user = super().create(validated_data)
        user.set_password(password)
        user.save()
        return user


class TaskSerializer(ModelSerializer):
    class Meta:
        model=MyTask
        fields = ['id', 'public_id' , 'name', 'description', 'complete' , 'Foreign_id']
        #extra_kwargs = { 
            #'password' : {'write_only':True}
        #}