from flask import Blueprint,request,jsonify, current_app
import uuid
from werkzeug.security import generate_password_hash
from .models import User
from .models import db
from flask_jwt_extended import jwt_required




user_bp = Blueprint('user', __name__) 


@user_bp.route('/user', methods =["GET"])
#@jwt_required()
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
#@jwt_required()
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
#@jwt_required()
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


