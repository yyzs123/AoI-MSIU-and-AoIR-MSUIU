#include<vector>
class Content
{
private:
    int id, t, vmc, used, sn;
    friend void sortContentByTime(std::vector<Content>& vec, bool rev);
    friend void sortContentByVmc(std::vector<Content>& vec, bool rev);
    friend void sortContentById(std::vector<Content>& vec);
    friend void printContentVec(const std::vector<Content> &vec);
public:
    Content();
    Content(int _id, int _t = 0, int _vmc = 0, int _used = 0, int _sn = 0):id(_id), t(_t), vmc(_vmc), used(_used), sn(_sn){};
    const int getid()const;
    const int gett()const;
    const int getvmc()const;
    const int getsn()const;
    void setused(const int _used);
    const int getused()const;
    void print()const;
};