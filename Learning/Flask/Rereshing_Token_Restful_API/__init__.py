from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_jwt_extended import JWTManager
from datetime import timedelta

db = SQLAlchemy()
app = Flask(__name__)
app.config['SECRET_KEY'] = 'very-secret-much-wow'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///db.sqlite'
app.config["JWT_ACCESS_TOKEN_EXPIRES"] = timedelta(minutes=2)
app.config["JWT_REFRESH_TOKEN_EXPIRES"] = timedelta(minutes=2)
jwt = JWTManager(app)
SQLALCHEMY_TRACK_MODIFICATIONS = True

    
with app.app_context():
        db.init_app(app)
        from .models import User,MyTask
        #db.drop_all() # in case of other aplcation trolling
        db.create_all()
    # import when needed to avoid circular import
from .task import task_bp as task_blueprint  # auth routes blueprint
from .user import user_bp as user_blueprint  # user blueprint  
from .auth import auth_bp as auth_blueprint #authentication blueprint
app.register_blueprint(task_blueprint)
app.register_blueprint(user_blueprint)
app.register_blueprint(auth_blueprint)