//
// Created by frank on 17.04.23.
//

#ifndef MULLEMAUS_OBJECTFACTORY_HPP
#define MULLEMAUS_OBJECTFACTORY_HPP

#include "mullemaus_api.hpp"
#include "basicobject.hpp"
#include <string>
#include <map>

namespace MM {

    extern "C" {

    //Von dieser Klasse müssen alle ObjectCreators abgeleitet werden,
    //damit die objecte dynamisch aus dateien geladen werden können
    MULLEMAUS_API class BaseCreator {
    public:
        //Gibt einen Zeiger auf ein erstelltes GameObject_Interface (egal welcher Type) zurück
        virtual BasicObject *CreateObject() const = 0;

        virtual ~BaseCreator() {}
    };

    MULLEMAUS_API class GameObjectFactory {
    public:

        //Neuen Typen regestrieren, um dynamisch Objekte zu erstellen
        bool RegisterType(std::string typeID, BaseCreator *creator);

        //Neues Objekt erstellen
        BasicObject *Create(std::string typeID);

        //Damit die Klasse ein Singleton ist, wir brauchen ja nur eine Instanze
        static GameObjectFactory *Instance() {
            if (pInstance == nullptr)
                pInstance = new GameObjectFactory();
            return pInstance;
        }

    private:


        GameObjectFactory() : pCreators() {}

        std::map<std::string, BaseCreator *> pCreators;

        static GameObjectFactory *pInstance;
    };

    }//extern "C"

} // MM

#endif //MULLEMAUS_OBJECTFACTORY_HPP
