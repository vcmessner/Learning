# Generated by Django 4.1.3 on 2022-12-10 21:55

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('pools', '0005_alter_myuser_last_token_created_at'),
    ]

    operations = [
        migrations.AlterField(
            model_name='myuser',
            name='token',
            field=models.CharField(blank=True, max_length=100, null=True),
        ),
    ]
