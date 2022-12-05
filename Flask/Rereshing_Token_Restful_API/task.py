from flask import Blueprint,request,jsonify
from .models import MyTask,User
from .models import db
import uuid
from flask_jwt_extended import jwt_required


task_bp = Blueprint('task', __name__) 

@task_bp.route('/task', methods=['GET'])
@jwt_required()
def get_all_task():
    current_user = User.get_token_user(request.headers['Authorization'][7::])
    tasks = MyTask.query.filter_by(user_id=current_user.id).all()
    output = []
    for task in tasks:
        output.append(task.to_dict())
    return jsonify({'Tasks': output})

@task_bp.route('/task/<public_id>', methods=['GET'])
@jwt_required()
def get_one_task(public_id):
    current_user = User.get_token_user(request.headers['Authorization'][7::])
    task = MyTask.query.filter_by(public_id=public_id,user_id=current_user.id).first()
    if not(task):
        return jsonify({'Message': "task not found"})
    return jsonify({'Tasks': task.to_dict()})

@task_bp.route('/task/', methods=['POST'])
@jwt_required()
def create_task():
    current_user = User.get_token_user(request.headers['Authorization'][7::])
    data=request.get_json()
    task = MyTask(name=data['name'],description=data['description'],public_id=str(uuid.uuid4()), complete=False, user_id= current_user.id)
    db.session.add(task)
    db.session.commit()
    return jsonify({'Message': "Task created"})

@task_bp.route('/task/<public_id>', methods=['PUT'])
@jwt_required()
def complete_task(public_id):
    current_user = User.get_token_user(request.headers['Authorization'][7::])
    task = MyTask.query.filter_by(public_id=public_id,user_id=current_user.id,).first()
    if not(task):
        return jsonify({'Message': "task not found"})
    task.complete = True
    db.session.commit()
    return  jsonify({'Message': "Task completed"})

@task_bp.route('/task/<public_id>', methods=['DELETE'])
@jwt_required()
def delete_one_task(public_id):
    current_user = User.get_token_user(request.headers['Authorization'][7::])
    task = MyTask.query.filter_by(public_id=public_id,user_id=current_user.id,).first()
    if not(task):
        return jsonify({'Message': "task not found"})
    db.session.delete(task)
    db.session.commit()
    return  jsonify({'Message': "Task deleted"})