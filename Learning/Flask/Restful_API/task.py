from flask import Blueprint,request,jsonify
from .models import MyTask
from .models import db
from .decorators import token_required


task_bp = Blueprint('task', __name__) 

@task_bp.route('/task', methods=['GET'])
@token_required
def get_all_task(current_user):
    tasks = MyTask.query.filter_by(user_id=current_user.id).all()
    output = []
    for task in tasks:
        output.append(task.to_dict())
    return jsonify({'Tasks': output})

@task_bp.route('/task/<task_id>', methods=['GET'])
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

@task_bp.route('/task/', methods=['POST'])
@token_required
def create_task(current_user):
    data=request.get_json()
    task = MyTask(text=data['text'], complete=False, user_id= current_user.id)
    db.session.add(task)
    db.session.commit()
    return jsonify({'Message': "Task created"})

@task_bp.route('/task/<task_id>', methods=['PUT'])
@token_required
def complete_task(current_user,task_id):
    task = MyTask.query.filter_by(id=task_id,user_id=current_user.id,).first()
    if not(task):
        return jsonify({'Message': "task not found"})
    task.complete = True
    db.session.commit()
    return  jsonify({'Message': "Task completed"})

@task_bp.route('/task/<task_id>', methods=['DELETE'])
@token_required
def delete_one_task(current_user,task_id):
    task = MyTask.query.filter_by(id=task_id,user_id=current_user.id,).first()
    if not(task):
        return jsonify({'Message': "task not found"})
    db.session.delete(task)
    db.session.commit()
    return  jsonify({'Message': "Task deleted"})