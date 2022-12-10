from django.db import models
from django.contrib.auth.models import AbstractUser
import uuid

class Drink(models.Model):
    name = models.CharField(max_length=100)

    def __str__(self):
        return self.name

class MyUser(models.Model):
    id = models.AutoField(primary_key = True,unique = True)
    public_id = models.UUIDField(default=uuid.uuid4, editable=False,unique = True)
    email =models.CharField(max_length=20,unique = True)
    username = models.CharField(max_length=20,unique = True)
    password =models.CharField(max_length=20,unique = True)
    name = models.CharField(max_length=20,unique = True)
    admin = models.BooleanField(default=False)
    token = models.CharField(max_length=36, blank=True, null=True)
    last_token_created_at =models.DateField(blank=True, null=True)
    #USERNAME_FIELD = 'username'
    #REQUIRED_FIELDS = []

    #def to_dict(self):
       # user_dict ={}
       # user_dict['public_id'] = self.public_id
       # user_dict['email'] = self.email
       # user_dict['username'] = self.username
      #  user_dict['name'] = self.name
      #  user_dict['admin'] = self.admin
      #  return user_dict
    
    #def get_token_user(token):
        #data = decode_token(token)
        #return User.query.filter_by(username=data['sub']['username']).first()

#class MyTask(models.Model):
   # __tablename__ = 'mytask'
   # id = models.IntegerField
   # public_id = models.CharField(max_length=20)
   # name = models.CharField(max_length=20)
   # description =models.CharField(max_length=50)
   # complete =  models.BooleanField
   # user_id = models.ForeignKey(MyUser, on_delete=models.CASCADE)
        
    #def to_dict(self):
    #    task_dict ={}
    #    task_dict['name'] = self.name
    #    task_dict['text'] = self.description
    #    task_dict['complete'] = self.complete
    #    task_dict['public_id']= self.public_id
    #    return task_dict


