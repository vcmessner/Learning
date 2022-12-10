import jwt, datetime
from rest_framework import exceptions
from rest_framework.authentication import get_authorization_header

access_duration = datetime.timedelta(minutes=2)
refresh_duration = datetime.timedelta(minutes=2)
valid_creation_window = datetime.timedelta(minutes=1)

def create_acess_token(id):
    return jwt.encode(
        {
            'user_id' : id,
            'exp' : datetime.datetime.utcnow() + datetime.timedelta(minutes=30),
            'iat' : datetime.datetime.utcnow()
        }, 'access_secret', algorithm='HS256')
    
def decode_acess_token(token):
    try:
        user = jwt.decode(token, 'access_secret', algorithms=['HS256'])
        return user['user_id']
    except:
        raise exceptions.AuthenticationFailed('auth failed')


def create_refresh_token(id):
   return jwt.encode(
        {
            'user_id' : id,
            'exp' : datetime.datetime.utcnow() + datetime.timedelta(days=30),
            'iat' : datetime.datetime.utcnow()
        }, 'refresh_secret', algorithm='HS256')


def decode_refresh_token(token):
    #try:
        print(token)
        user = jwt.decode(token, 'refresh_secret', algorithms=['HS256'])
        return user['user_id']
    #except:
        #raise exceptions.AuthenticationFailed('auth failed')

def authenticate_token(request):
        auth = get_authorization_header(request).split()
        if auth and len(auth) == 2:
            token = auth[1].decode('utf-8')
            id = decode_acess_token(token)
            return id
        return None