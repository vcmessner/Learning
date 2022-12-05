from . import LoginDB
from flask_login import UserMixin

class User(UserMixin,LoginDB.Model):
    id = LoginDB.Column(LoginDB.Integer, primary_key=True)
    email = LoginDB.Column(LoginDB.String(20), unique=True)
    password = LoginDB.Column(LoginDB.String(20))
    name = LoginDB.Column(LoginDB.String(20))