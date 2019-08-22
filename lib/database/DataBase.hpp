/***
 *  @file : CommandList.hpp
 * 	@date 2019/08/19
 *  @author 하정현(seokbong60@gmail.com) Team:SweetCase Project (1-person Team)
 *  @brief : 데이터를 관리하는 데이터베이스 엔진 클래스 입니다.
 * 
 ***/

#ifndef DATABASE_HPP
# define DATABASE_HPP

#include <list>
#include <map>
#include <string>
#include <mutex>

#include "../structure/DataElement.hpp"
#include "../packet/Packet.hpp"
#include "../threadAdapter/AdapterThreadUtility.hpp"

using namespace std;
using namespace ThreadAdapter;
using namespace structure;

namespace SKVS_DataBase {

    class DataBase : public std::enable_shared_from_this<DataBase> {
    private:
        //member
        list<DataElement*> dataBase;
        map<DataElement*, unique_ptr<mutex>> mutexMap;
        weak_ptr<AdapterThreadUtility> queueAdapter;

        //데이터 루트 찾기
        DataElement* findDatabyRoot(const string root, string& errorMsg);

        //예외처리
        void exceptError(SendCmdPacket& _requestPacket, string errorMsg);

        //Data Functions
        void create(SendCmdPacket& _requestPacket);
        void drop(SendCmdPacket& _requestPacket);
        void insert(SendCmdPacket& _requestPacket);

    public:
        explicit DataBase(shared_ptr<AdapterThreadUtility>& adapter) {
            queueAdapter = adapter;
        }
        //어댑터 연결 여부
        inline const bool checkAdapter(void) noexcept {
            shared_ptr<AdapterThreadUtility> adapterChecker = queueAdapter.lock();
            if( adapterChecker ) return true;
            else return false;
        }
        //명령문 실행
        void runCmd(SendCmdPacket& _requestPacket);
        weak_ptr<DataBase> getWeekPtr() { return weak_from_this(); }
    };
}

#endif