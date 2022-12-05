from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager

db = SQLAlchemy()

def create_app():

    #init
    app = Flask(__name__)
    app.config['SECRET_KEY'] = 'very-secret-much-wow'
    app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///db.sqlite'
    db.init_app(app)
    app.app_context().push()

    login_manager = LoginManager()
    login_manager.login_view = 'auth.login'
    login_manager.init_app(app)

    from .models import User #circular import if out, fix later

    @login_manager.user_loader
    def load_user(user_id):
        # since the user_id is just the primary key of our user table, use it in the query for the user
        return User.query.get(int(user_id))


    #lets define our blueprints and register them
    from .auth import auth as auth_blueprint  # auth routes blueprint
    from .main import main as main_blueprint  # non-auth blueprint
    from .user import user as user_blueprint  # user blueprint
    
    app.register_blueprint(auth_blueprint)
    app.register_blueprint(main_blueprint)
    app.register_blueprint(user_blueprint)

    return app