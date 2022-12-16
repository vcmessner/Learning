from flask import Blueprint,request,jsonify,make_response, current_app
import uuid
from werkzeug.security import generate_password_hash, check_password_hash
from .models import User
from .models import db
from .decorators import token_required
import datetime
import jwt

user_bp = Blueprint('user', __name__) 

@user_bp.route('/user', methods =["GET"])
@token_required
def get_all_users(current_user):
#def get_all_users(): # in case of drop you need to get the user public id
    if not current_user.admin:
        return jsonify({'message': "Permission denied"})    
    data = User.query.all()
    output=[]
    for i in data:
        output.append(i.to_dict())
    return jsonify({'usernames': output})

@user_bp.route('/user/<public_id>', methods =["GET"])
@token_required
def get_one_user(current_user,public_id):
    if not current_user.admin:
        return jsonify({'message': "Permission denied"})
    data = User.query.filter_by(public_id=public_id)
    if (data.count()==0):
        return jsonify({'message': "No user found"})    
    return jsonify({'message': data.first().username})

@user_bp.route('/user', methods =["POST"])
@token_required
def create_user(current_user):
#def create_user(): #in case of drop you need to create user without admin permission
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


@user_bp.route('/user/<public_id>', methods =["PUT"])
@token_required
def promote_user(current_user,public_id):
#def promote_user(public_id): #in case of drop you need to set user as admin
    if not current_user.admin:
        return jsonify({'message': "Prmission denied"})
    data = User.query.filter_by(public_id=public_id)
    if (data.count()==0):
        return jsonify({'message': "No user found"})
    data.first().admin = True
    db.session.commit()
    return jsonify({'message':"user promoted"})


@user_bp.route('/user/<public_id>', methods =["DELETE"])
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

@user_bp.route('/login')
def login():
    auth = request.authorization
    token_duration=30 #minutes
    if (not auth) or (not auth.username) or (not auth.password):
        return make_response("could not verify",401,{'WWW.Authenticate' :'Basic realm = "login required"'})
    user = User.query.filter_by(username=auth.username).first()
    if not user:
        return make_response("could not verify",401,{'WWW.Authenticate' :'Basic realm = "login required"'})
    if check_password_hash(user.password, auth.password):
        token = jwt.encode({'public_id': user.public_id,'exp': datetime.datetime.utcnow()+datetime.timedelta(minutes=token_duration)},current_app.config['SECRET_KEY'],algorithm="HS256")
        return jsonify({'token': token})
    return make_response("could not verify",401,{'WWW.Authenticate' :'Basic realm = "login required"'})