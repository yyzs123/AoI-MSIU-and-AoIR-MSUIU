#include"Content.h"
#include<algorithm>
#include<iostream>
void sortContentByTime(std::vector<Content> &vec, bool rev)
{
    if(rev)
        sort(vec.begin(), vec.end(), [&](const Content &x, const Content &y){
            return x.t > y.t;
        });
    else
        sort(vec.begin(), vec.end(), [&](const Content &x, const Content &y){
            return x.t < y.t;
        });
}
void sortContentByVmc(std::vector<Content> &vec, bool rev)
{
    if(rev)
        sort(vec.begin(), vec.end(), [&](const Content &x, const Content &y){
            return x.vmc > y.vmc;
        });
    else    
        sort(vec.begin(), vec.end(), [&](const Content &x, const Content &y){
            return x.vmc < y.vmc;
        });
}
void sortContentById(std::vector<Content> &vec)
{
    sort(vec.begin(), vec.end(), [&](const Content &x, const Content &y){
        return x.id < y.id;
    });
}
void printContentVec(const std::vector<Content> &vec)
{
    for(const Content &content:vec)
        if(content.getused())
            content.print();
    std::cout << std::endl;
}
const int Content::getid()const{ return id; }
const int Content::gett()const{ return t; }
const int Content::getvmc()const{ return vmc; }
const int Content::getsn()const{ return sn;}
void Content::setused(const int _used){ used = _used; }
const int Content::getused()const{ return used; }
void Content::print()const
{
    std::cout << "(" << id << ", " << t << ", " << vmc <<" " << used << " " << sn << ") ";
}