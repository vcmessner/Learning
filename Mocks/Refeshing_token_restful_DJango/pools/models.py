from django.db import models
from django.contrib.auth.models import AbstractUser
import uuid

class MyUser(AbstractUser):
    id = models.AutoField(primary_key = True,unique = True)
    public_id = models.UUIDField(default=uuid.uuid4, editable=False,unique = True)
    email =models.CharField(max_length=20,unique = True)
    username = models.CharField(max_length=20,unique = True)
    password =models.CharField(max_length=20,unique = True)
    name = models.CharField(max_length=20,unique = True)
    admin = models.BooleanField(default=False)
    token = models.CharField(max_length=300, blank=True, null=True)
    last_token_created_at =models.DateTimeField(blank=True, null=True)


class MyTask(models.Model):
    id = models.AutoField(primary_key = True,unique = True)
    public_id = models.UUIDField(default=uuid.uuid4, editable=False,unique = True)
    name = models.CharField(max_length=20)
    description =models.CharField(max_length=50)
    complete =  models.BooleanField(default=False)
    Foreign_id = models.ForeignKey(MyUser, on_delete=models.CASCADE)
