#from django.db import models
#from django.contrib.auth.models import AbstractUser
#import uuid

#class MyUser(AbstractUser):
    #pass
    #id = models.AutoField(primary_key = True,unique = True)
    #public_id = models.UUIDField(default=uuid.uuid4, editable=False,unique = True)
    #email =models.CharField(max_length=20,unique = True)
    #username = models.CharField(max_length=20,unique = True)
    #password =models.CharField(max_length=20,unique = True)
    #name = models.CharField(max_length=20,unique = True)
    #admin = models.BooleanField(default=False)
    #token = models.CharField(max_length=36, blank=True, null=True)
    #last_token_created_at =models.DateField(blank=True, null=True)
