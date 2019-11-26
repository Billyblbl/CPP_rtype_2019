/*
** EPITECH PROJECT, 2019
** 
** File description:
** 
*/


#ifndef ASSETCACHE_HPP_
#define ASSETCACHE_HPP_
#include <string>
#include <memory>
#include <unordered_map>
#include <any>

class AssetCache {
    public:
    	template<typename T>
        auto load(const std::string &key)
        {
            auto it = map.find(key);
            if (it == map.end() || it->second.expired()) 
                return emplace<T>(key, key);
            else {
                auto sptr = it->second.lock();
                if (sptr == nullptr)
                    return emplace<T>(key, key);
                else
                    return sptr;
            }
        }
    	
        template<typename T, typename... Args>
        auto emplace(const std::string &key, Args&&... args)
        {
            auto sptr = std::make_shared<std::any>(std::in_place_type_t<T>{}, std::forward<Args>(args)...);
            std::weak_ptr<std::any> wptr = sptr;
            map[key] = wptr;
            return (sptr);
        }
    
        template<typename T>
        void push(const std::string &key, std::shared_ptr<T> sptr)
        {
            std::weak_ptr<std::any> wptr = sptr;
            map[key] = wptr;
        }

        template<typename T>
        auto get(const std::string &key)
        {
            auto sptr = map.at(key).lock();
            if (sptr == nullptr)
                throw std::runtime_error("key not found");
            return sptr;
        }

        template<typename T>
        auto get(const std::string &key) const
        {
            auto sptr = map.at(key).lock();
            if (sptr == nullptr)
                throw std::runtime_error("key not found");
            return sptr;
        }

        static AssetCache   &getGlobalCache();

    private:
	    std::unordered_map<std::string, std::weak_ptr<std::any>> map;

};

#endif /* !ASSETCACHE_HPP_ */
