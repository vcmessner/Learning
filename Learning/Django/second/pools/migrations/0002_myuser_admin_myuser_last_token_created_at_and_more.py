# Generated by Django 4.1.3 on 2022-12-10 19:39

from django.db import migrations, models
import uuid


class Migration(migrations.Migration):

    dependencies = [
        ('pools', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='myuser',
            name='admin',
            field=models.BooleanField(default=False),
        ),
        migrations.AddField(
            model_name='myuser',
            name='last_token_created_at',
            field=models.DateField(blank=True, null=True),
        ),
        migrations.AddField(
            model_name='myuser',
            name='name',
            field=models.CharField(default='none', max_length=20, unique=True),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='myuser',
            name='public_id',
            field=models.UUIDField(default=uuid.uuid4, editable=False, unique=True),
        ),
        migrations.AddField(
            model_name='myuser',
            name='token',
            field=models.CharField(blank=True, max_length=36, null=True),
        ),
        migrations.AlterField(
            model_name='myuser',
            name='email',
            field=models.CharField(max_length=20, unique=True),
        ),
        migrations.AlterField(
            model_name='myuser',
            name='id',
            field=models.AutoField(primary_key=True, serialize=False, unique=True),
        ),
        migrations.AlterField(
            model_name='myuser',
            name='password',
            field=models.CharField(max_length=20, unique=True),
        ),
        migrations.AlterField(
            model_name='myuser',
            name='username',
            field=models.CharField(max_length=20, unique=True),
        ),
    ]
