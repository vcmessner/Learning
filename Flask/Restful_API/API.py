"""
from flask_login import UserMixin
from sqlalchemy.orm import relationship
from flask import Blueprint,request,jsonify,Flask, make_response
from flask_sqlalchemy import SQLAlchemy
import uuid
from werkzeug.security import generate_password_hash, check_password_hash
import jwt
import datetime
from functools import wraps

app = Flask(__name__)
app.config['SECRET_KEY'] = 'very-secret-much-wow'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///db.sqlite'
db = SQLAlchemy(app)
db.init_app(app)
app.app_context().push()

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


def token_required(f):
    # info on @wraps
    # __module__, __name__, __qualname__, __doc__, and __annotations__ are copied to the main function/ this copy doesnt happen during a def wrapper
    #  as consequeces the wrapper code will execute even when the provided arguments are invalid 
    #  the wrapper code can not easily access an argument using its name, from the received *args, **kwargs 
    #  so in case of performance issues always give a check in the wraps
    #  Update a wrapper function to look like the wrapped function
    @wraps(f) 
    def decorated(*args, **kwargs):
        token = None
        if 'x-acess-token' in request.headers:
            token = request.headers['x-acess-token']
        if not token:
            return jsonify({'message': 'no token found'})
        try:
            data = jwt.decode(token, app.config['SECRET_KEY'],algorithms="HS256")
            current_user = User.query.filter_by(public_id=data['public_id']).first()
        except:
            return jsonify({'message': 'invalid token'})  
        return f(current_user,*args, **kwargs)
    return decorated



@app.route('/user', methods =["GET"])
@token_required
def get_all_users(current_user):
    if not current_user.admin:
        return jsonify({'message': "Prmission denied"})    
    data = User.query.all()
    output=[]
    for i in data:
        output.append(i.to_dict())
    return jsonify({'usernames': output})

@app.route('/user/<public_id>', methods =["GET"])
@token_required
def get_one_user(current_user,public_id):
    if not current_user.admin:
        return jsonify({'message': "Prmission denied"})
    data = User.query.filter_by(public_id=public_id)
    if (data.count()==0):
        return jsonify({'message': "No user found"})    
    return jsonify({'message': data.first().username})

@app.route('/user', methods =["POST"])
@token_required
def create_user(current_user):
    if not current_user.admin:
        return jsonify({'message': "Prmission denied"})
    data = request.get_json()
    hashed_password = generate_password_hash(data["password"],method='sha256')
    new_user = User(public_id=str(uuid.uuid4()),username=data['username'],\
                    email=data['email'],name=data['name'],password=hashed_password,\
                    admin=False)
    db.session.add(new_user)
    db.session.commit();
    return jsonify({'message':"user created"})


@app.route('/user/<public_id>', methods =["PUT"])
@token_required
def promote_user(current_user,public_id):
    if not current_user.admin:
        return jsonify({'message': "Prmission denied"})
    data = User.query.filter_by(public_id=public_id)
    if (data.count()==0):
        return jsonify({'message': "No user found"})
    data.first().admin = True
    db.session.commit()
    return jsonify({'message':"user promoted"})


@app.route('/user/<public_id>', methods =["DELETE"])
@token_required
def delete_user(current_user,public_id):
    if not current_user.admin:
        return jsonify({'message': "Prmission denied"})
    data = User.query.filter_by(public_id=public_id)
    if (data.count()==0):
        return jsonify({'message': "No user found"})
    db.session.delete(data.first())
    db.session.commit()
    return jsonify({'message': "user deleted"})

@app.route('/login')
def login():
    auth = request.authorization
    token_duration=30 #minutes
    print("1")
    if (not auth) or (not auth.username) or (not auth.password):
        return make_response("could not verify",401,{'WWW.Authenticate' :'Basic realm = "login required"'})
    user = User.query.filter_by(username=auth.username).first()
    print("2")
    if not user:
        return make_response("could not verify",401,{'WWW.Authenticate' :'Basic realm = "login required"'})
    print("3")
    if check_password_hash(user.password, auth.password):
        token = jwt.encode({'public_id': user.public_id,'exp': datetime.datetime.utcnow()+datetime.timedelta(minutes=token_duration)},app.config['SECRET_KEY'],algorithm="HS256")
        return jsonify({'token': token})
    print("4")
    return make_response("could not verify",401,{'WWW.Authenticate' :'Basic realm = "login required"'})

@app.route('/task', methods=['GET'])
@token_required
def get_all_task(current_user):
    tasks = MyTask.query.filter_by(user_id=current_user.id).all()
    output = []
    for task in tasks:
        output.append(task.to_dict())
    return jsonify({'Tasks': output})

@app.route('/task/<task_id>', methods=['GET'])
@token_required
def get_one_task(current_user,task_id):
    task = MyTask.query.filter_by(id=task_id,user_id=current_user.id,).first()
    if not(task):
        return jsonify({'Message': "task not found"})
    task_data={}
    task_data['id'] = task.id
    task_data['text'] = task.text
    task_data['complete'] = task.complete
    return jsonify({'Tasks': task_data})
    return ''

@app.route('/task/', methods=['POST'])
@token_required
def create_task(current_user):
    data=request.get_json()
    task = MyTask(text=data['text'], complete=False, user_id= current_user.id)
    db.session.add(task)
    db.session.commit()
    return jsonify({'Message': "Task created"})

@app.route('/task/<task_id>', methods=['PUT'])
@token_required
def complete_task(current_user,task_id):
    task = MyTask.query.filter_by(id=task_id,user_id=current_user.id,).first()
    if not(task):
        return jsonify({'Message': "task not found"})
    task.complete = True
    db.session.commit()
    return  jsonify({'Message': "Task completed"})

@app.route('/task/<task_id>', methods=['DELETE'])
@token_required
def delete_one_task(current_user,task_id):
    task = MyTask.query.filter_by(id=task_id,user_id=current_user.id,).first()
    if not(task):
        return jsonify({'Message': "task not found"})
    db.session.delete(task)
    db.session.commit()
    return  jsonify({'Message': "Task deleted"})

"""