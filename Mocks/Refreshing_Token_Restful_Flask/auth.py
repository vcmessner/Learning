from . import jwt,db
from datetime import datetime, timedelta
from datetime import timezone
from .models import TokenBlocklist
from flask_jwt_extended import create_access_token, jwt_required, get_jwt_identity, create_refresh_token, get_jwt
from werkzeug.security import generate_password_hash, check_password_hash
from flask import Blueprint,request,jsonify,make_response, current_app
from .models import User

auth_bp = Blueprint('auth', __name__) 
Refresh_last_creation=None
Access_last_creation=None
min_expiration_time=60 #seconds

@jwt.token_in_blocklist_loader
def check_if_token_revoked(jwt_header, jwt_payload: dict) -> bool:
    jti = jwt_payload["jti"]
    token = db.session.query(TokenBlocklist.id).filter_by(jti=jti).scalar()
    return token is not None


@auth_bp.route('/login')
def login():
    global Refresh_last_creation,Access_last_creation, min_expiration_time
    auth = request.authorization
    if (not auth) or (not auth.username) or (not auth.password):
        return make_response("could not verify",401,{'WWW.Authenticate' :'Basic realm = "login required"'})
    user = User.query.filter_by(username=auth.username).first()
    if not user:
        return make_response("could not verify",401,{'WWW.Authenticate' :'Basic realm = "login required"'})
    if check_password_hash(user.password, auth.password):
        Refresh_last_creation=user.last_token_created_at.replace(tzinfo=timezone.utc)
        if(Refresh_last_creation):
            print(last_creation)
            print (datetime.now(timezone.utc))
            diff = datetime.now(timezone.utc) - last_creation
            print("Token created " + str(diff.seconds) + " seconds ago")
            print(current_app.config["JWT_ACCESS_TOKEN_EXPIRES"].seconds)
            if(current_app.config["JWT_ACCESS_TOKEN_EXPIRES"].seconds-diff.seconds)>=min_expiration_time:
                return jsonify({'Refresh Token still Valid: Acess': user.token})      
        Access_last_creation=datetime.now(timezone.utc)                 
        Refresh_last_creation=Access_last_creation
        token = create_access_token(identity={"username":auth.username})
        refresh = create_refresh_token(identity=user.id) 
        user.last_token_created_at = Refresh_last_creation
        user.token=refresh #todo: token should be hashed when saved in the db
                           #otherwise any programmer can impersonate a user 
        db.session.commit()
        
        return jsonify({'Acess': token, "Refresh":refresh})
    return make_response("could not verify",401,{'WWW.Authenticate' :'Basic realm = "login required"'})

@auth_bp.route('/refresh')
@jwt_required(refresh=True)  #refresh token can only be created 1 min before the expected expiration of the 
def refresh():    
    global last_creation, min_expiration_time
    identity = get_jwt_identity();
    diff = datetime.now(timezone.utc) - last_creation
    print("Token created " + str(diff.seconds) + " seconds ago")
    print(current_app.config["JWT_ACCESS_TOKEN_EXPIRES"].seconds)

    if(current_app.config["JWT_ACCESS_TOKEN_EXPIRES"].seconds-diff.seconds)<min_expiration_time:      #pass
        token = create_access_token(identity=identity, fresh=False) 
        last_creation = datetime.now(timezone.utc)
        return jsonify({'token': token})
    return jsonify({'Message': "Token created recently. Please wait and try again"})
@auth_bp.route("/logout", methods=["POST"]) # All should be ok from server sider however since 2013 browsers will pre-fetch pages, making post more coherent in a practical approach
                                            #https://stackoverflow.com/questions/3521290/logout-get-or-post
                                            #Front end must send tow requests for delete each kind of token
@jwt_required(verify_type=False)
def logout():
    jti = get_jwt()["jti"]    
    now = datetime.now(timezone.utc)
    db.session.add(TokenBlocklist(jti=jti, created_at=now))
    db.session.commit()
    return jsonify({'message':"JWT revoked"})