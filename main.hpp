#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <cmath>


#define MAIN_HPP
#ifdef MAIN_HPP

namespace biba
    {
        template<typename T>class Allocator;
        template<typename T> class MemoryManager;

        template<typename T> class Allocator
        {
            public:
            void* biba() noexcept
            {
                to_rotate = sbrk(size);
                
                if(to_rotate == reinterpret_cast<void*>(-1))
                {
                    std::cerr << "Error\n" << std::flush;
                    to_rotate = nullptr;
                    return nullptr;
                }

                capacity += size;
                return to_rotate;
            }

            void* freedom() noexcept
            {
              
                    to_rotate = sbrk(-size);
                    to_rotate = nullptr;
                    capacity -= size;
                
                return to_rotate;
            } 
            
            private:
            const static size_t size = sizeof(T);

            protected:
            static inline size_t capacity {};
            void *to_rotate; 
        };


        template<typename T> class MemoryManager:protected Allocator<T>
            {
                public:
                MemoryManager()
                {
                     Allocator<T>::biba();
                }
                explicit MemoryManager(const T& _variable):InType(_variable) 
                {
                     Allocator<T>::biba();
                }
                explicit MemoryManager(const T&& _variable):InType(std::move(_variable))
                {
                     Allocator<T>::biba();
                }
                MemoryManager &operator=(MemoryManager&& value) noexcept = default;
                MemoryManager &operator=(const MemoryManager& value) noexcept = default;

                MemoryManager &operator=(T&& value) noexcept 
                {
                    InType = value;
            
                    return *this;
                }
                MemoryManager &operator=(T& value) noexcept 
                {
                    InType = value;
            
                    return *this;
                }

                ~MemoryManager()
                {
                    Allocator<T>::freedom();
                };
                

                void Capasity()
                {
                    std::cout << "Capacity of memory alloc: " << Allocator<T>::capacity << " MB\n" << std::flush;
                }

                void Mem_checker()
                {
                     if(Allocator<T>::to_rotate == nullptr)
                     {
                        std::cout << "No one object with allocated memory is not available\n" << std::flush;
                     }
                     else
                     {
                        std::cout << "Memory allocate now!" << '\n' <<  std::flush;
                     }
                }

                private:
                T InType;

            };

       
           


    };

#endif