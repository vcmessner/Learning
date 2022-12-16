from flask import Flask
from flask_sqlalchemy import SQLAlchemy

db = SQLAlchemy()
app = Flask(__name__)
app.config['SECRET_KEY'] = 'very-secret-much-wow'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///db.sqlite'
    #db.init_app(app)
SQLALCHEMY_TRACK_MODIFICATIONS = True
    
with app.app_context():
        db.init_app(app)
        from .models import User,MyTask
        #db.drop_all() # in case of other aplcation trolling
        db.create_all()
    # import when needed to aoid circular import
from .task import task_bp as task_blueprint  # auth routes blueprint
from .user import user_bp as user_blueprint  # user blueprint  
app.register_blueprint(task_blueprint)
app.register_blueprint(user_blueprint)