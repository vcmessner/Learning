from . import db
from flask_login import UserMixin
from sqlalchemy.orm import relationship

#user and tasks have a 1:N relationship
#so the user_id must be in th task as a ForeignKey

class User(UserMixin,db.Model):
    __tablename__ = 'user'
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(20), unique=True, nullable=False)
    username = db.Column(db.String(20), unique=True, nullable=False)
    password = db.Column(db.String(20), nullable=False)
    name = db.Column(db.String(20), nullable=False)
    admin = db.Column(db.Boolean)
    #relationship ("class name", back_populates="variable_to_be_populated")
    tasks = relationship("Mytask", back_populates="user")

class MyTask(db.Model):
    __tablename__ = 'mytask'
    id = db.Column(db.Integer, primary_key=True)
    Text = db.Column(db.String(50))
    complete = db.Column(db.Boolean)
    user_id = db.Column(db.Integer, db.ForeignKey('request.id'))
    user = relationship("User", back_populates="tasks")
