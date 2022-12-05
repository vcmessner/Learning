from . import db
from flask_login import UserMixin
from sqlalchemy.orm import relationship



class User(UserMixin,db.Model):
    __tablename__ = 'user'
    id = db.Column(db.Integer, primary_key=True)
    public_id = db.Column(db.String(20),unique=True, nullable=False)
    email = db.Column(db.String(20), unique=True, nullable=False)
    username = db.Column(db.String(20), unique=True, nullable=False)
    password = db.Column(db.String(20), nullable=False)
    name = db.Column(db.String(20), nullable=False)
    admin = db.Column(db.Boolean)
    #relationship ("class name", back_populates="variable_to_be_populated")
    tasks = relationship("MyTask", back_populates="user")

    def to_dict(self):
        user_dict ={}
        user_dict['public_id'] = self.public_id
        user_dict['email'] = self.email
        user_dict['username'] = self.username
        user_dict['name'] = self.name
        user_dict['admin'] = self.admin
        return user_dict

class MyTask(db.Model):
    __tablename__ = 'mytask'
    id = db.Column(db.Integer, primary_key=True)
    text = db.Column(db.String(50))
    complete = db.Column(db.Boolean)
    user_id = db.Column(db.Integer, db.ForeignKey('user.id'))
    user = relationship("User", back_populates="tasks")
    
    def to_dict(self):
        task_dict ={}
        task_dict['text'] = self.text
        task_dict['complete'] = self.complete
        return task_dict
