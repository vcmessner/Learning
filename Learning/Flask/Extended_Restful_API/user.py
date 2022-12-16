from flask import Blueprint,request,jsonify,make_response, current_app
import uuid
from werkzeug.security import generate_password_hash, check_password_hash
from .models import User
from .models import db
import datetime
from flask_jwt_extended import create_access_token, jwt_required, decode_token

user_bp = Blueprint('user', __name__) 

@user_bp.route('/user', methods =["GET"])
@jwt_required()
def get_all_users():
    data = User.query.all()
    output=[]
    for i in data:
        output.append(i.to_dict())
    return jsonify({'usernames': output})

@user_bp.route('/user/<public_id>', methods =["GET"])
@jwt_required()
def get_one_user(public_id):    
    data = User.query.filter_by(public_id=public_id)
    if (data.count()==0):
        return jsonify({'message': "No user found"})    
    return jsonify({'message': data.first().username})

@user_bp.route('/user', methods =["POST"])
@jwt_required()
def create_user():
    data = request.get_json()
    hashed_password = generate_password_hash(data["password"],method='sha256')
    new_user = User(public_id=str(uuid.uuid4()),username=data['username'],\
                    email=data['email'],name=data['name'],password=hashed_password,\
                    admin=False)
    db.session.add(new_user)
    db.session.commit();
    return jsonify({'message':"user created"})


@user_bp.route('/user/<public_id>', methods =["PUT"])
@jwt_required()
def promote_user(public_id):
    data = User.query.filter_by(public_id=public_id)
    if (data.count()==0):
        return jsonify({'message': "No user found"})
    data.first().admin = True
    db.session.commit()
    return jsonify({'message':"user promoted"})


@user_bp.route('/user/<public_id>', methods =["DELETE"])
@jwt_required()
def delete_user(public_id):
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
        token = create_access_token(identity={"username":auth.username},expires_delta=datetime.timedelta(minutes=token_duration))
        return jsonify({'token': token})
    return make_response("could not verify",401,{'WWW.Authenticate' :'Basic realm = "login required"'})