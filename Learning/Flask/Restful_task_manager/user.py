from flask import Blueprint,request,jsonify
import uuid
from werkzeug.security import generate_password_hash, check_password_hash
from .models import User
from . import db


#vincular blueprint de nome main a esse aquivo py pelo sistema de nomes
user = Blueprint('user', __name__) 

@user.route('/user', methods =["GET"])
def get_all_users():
    return ""

@user.route('/usr/<user_id>', methods =["GET"])
def get_one_user():
    return ""

@user.route('/usr/<user_id>', methods =["POST"])
def create_user():
    data = request.get_json()
    hashed_password = generate_password_hash(data["password"],method='sha256')
    new_user = User(public_id=str(uuid.uuid4()),username=data['username'],\
                    email=data['email'],name=data['name'],password=hashed_password,\
                    admin=False)
    db.session.add(new_user)
    db.session.commit();
    return ""


@user.route('/usr/<user_id>', methods =["PUT"])
def promote_user():
    return ""


@user.route('/usr/<user_id>', methods =["DELETE"])
def delete_user():
    return ""
