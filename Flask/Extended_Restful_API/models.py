from . import db
from flask_login import UserMixin
from sqlalchemy.orm import relationship
from flask_jwt_extended import decode_token



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
    
    def get_token_user(token):
        data = decode_token(token)
        return User.query.filter_by(username=data['sub']['username']).first()

class MyTask(db.Model):
    __tablename__ = 'mytask'
    id = db.Column(db.Integer, primary_key=True)
    public_id = db.Column(db.String(20),unique=True, nullable=False)
    name = db.Column(db.String(20), nullable=False)
    description = db.Column(db.String(50), nullable=False)
    complete = db.Column(db.Boolean)
    user_id = db.Column(db.Integer, db.ForeignKey('user.id'))
    user = relationship("User", back_populates="tasks")
    
    def to_dict(self):
        task_dict ={}
        task_dict['name'] = self.name
        task_dict['text'] = self.description
        task_dict['complete'] = self.complete
        task_dict['public_id']= self.public_id
        return task_dict
