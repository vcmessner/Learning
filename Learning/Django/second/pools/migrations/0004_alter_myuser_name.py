# Generated by Django 4.1.3 on 2022-12-10 19:39

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('pools', '0003_alter_myuser_name'),
    ]

    operations = [
        migrations.AlterField(
            model_name='myuser',
            name='name',
            field=models.CharField(max_length=20, unique=True),
        ),
    ]