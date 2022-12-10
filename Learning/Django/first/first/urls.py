"""first URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.1/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from . import views
from rest_framework.urlpatterns import format_suffix_patterns
from .views import LoginApiView,UserAPIView,RefreshAPIView,LogoutAPIView

#token creation
from rest_framework_simplejwt.views import TokenObtainPairView,TokenRefreshView



urlpatterns = [
    path('admin/', admin.site.urls),
    #path('drinks/', views.drink_list),
    #path('drinks/<int:id>', views.drink_detail),
    #path('user/', views.get_all_users),
    #path('User/<int:id>', views.user_info),
    path('user/create', views.create_user),
    path('user/login', LoginApiView.as_view()),
    path('user/logout', LogoutAPIView.as_view()),
    path('user/', UserAPIView.as_view()),
    path('user/refresh', RefreshAPIView.as_view()),




    #path('token/', TokenObtainPairView.as_view()), #credentials on body by default wtf
    #path('token/refresh', RefreshAPIView.as_view()),

]

urlpatterns = format_suffix_patterns(urlpatterns)


