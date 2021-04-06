#include"user.h"
#include<iostream>
namespace user_s {
user_s::user::user(){

    std::cout<<"一个纯路人用户出现";
}

int user_s::user::LogIn(){
    return 0;
}

int user_s::user::SendMessage(){
    return 0;
}
void user_s::user::SetBaseInformation() {
    std::cout<<"请输入您的姓名:";
    std::cin>>this->Name;
    std::cout<<"请输入您的性别:";
    std::cin>>this->Sex;
    std::cout<<"请输入您的年龄:";
    std::cin>> this->Age;
    std::cout<<"请输入您的个人简介:";
    std::cin>>this->Intro;

}
void user_s::user::PrintInfo() {
    std::cout<<this->Name<<std::endl;
    std::cout<<this->Sex<<std::endl;
    std::cout<<this->Age<<std::endl;
    std::cout<<this->Intro<<std::endl;
}

}