/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

Copyright (c) 2016 halx99@live.com

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef _CCCREATE_HELPER_H_
#define _CCCREATE_HELPER_H_

/*
** CreateHelper for cocos2d's autorelease objects
*/
namespace cocos2d {

template<typename _Ty, bool>
struct traits_init{};

template<typename _Ty>
struct traits_init<_Ty, false>
{
    template<typename..._Args>
    static bool delayed_init(_Ty* ccobj, const _Args&...args)
    { // init use 'init' member func with more than 1 args
        return ccobj->init(args...);
    }
};

template<typename _Ty>
struct traits_init<_Ty, true>
{
    template<typename _Fty, typename..._Args>
    static bool delayed_init(_Ty* ccobj, const _Fty& memf, const _Args&...args)
    { // init use specific member func with more than 1 args
        return std::mem_fn(memf)(ccobj, args...);
    }

    template<typename _Fty>
    static bool delayed_init(_Ty* ccobj, const _Fty& memf)
    { // init use specific member func without arg
        return std::mem_fun(memf)(ccobj);
    }
};

template<typename _Ty>
class CreateHelper
{
    typedef CreateHelper<_Ty> _Myt;
public:
    template<typename ..._Args>
    static _Ty* create(const _Args&...args)
    {
        auto ccobj = new(std::nothrow) _Ty();

        if (ccobj != nullptr && CreateHelper<_Ty>::delayed_init(ccobj, args...))
        {
            ccobj->autorelease();
            return ccobj;
        }

        CC_SAFE_RELEASE_NULL(ccobj);

        return ccobj;
    }



    template<typename _Arg1, typename..._Args>
    static bool delayed_init(_Ty* ccobj, const _Arg1& memf, const _Args&...args)
    {
        return traits_init<_Ty, std::is_member_function_pointer<_Arg1>::value>::delayed_init(ccobj, memf, args...);
    }

    static bool delayed_init(_Ty* ccobj)
    { // init use 'init' member func without arg
        return ccobj->init();
    }
};

};

#endif
