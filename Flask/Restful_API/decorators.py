from .models import User
from functools import wraps
from flask import request,jsonify, current_app
import jwt



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
            data = jwt.decode(token, current_app.config['SECRET_KEY'],algorithms="HS256")
            current_user = User.query.filter_by(public_id=data['public_id']).first()
        except:
            return jsonify({'message': 'invalid token'})  
        return f(current_user,*args, **kwargs)
    return decorated

    