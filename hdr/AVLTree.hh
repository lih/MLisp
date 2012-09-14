#ifndef INCLUDED_AVL_TREE_HH
#define INCLUDED_AVL_TREE_HH

#include <functional> // for std::less

#include "FlaggedPtr.hh"
#include "Utils.hh"      // For min & max functions 

namespace Utils {
    template<class _T,class _Less=std::less<_T> >
    class AVLTree {
    public:
        // Declarations
        class Node;

    private:
        // Utility typedefs
        typedef FlaggedPtr<Node> FPN;

    public:
        // Public subclasses
        class Node {
        private:
            // Friends
            friend class AVLTree;

        private:
            // Properties
            _T   m_value;
            FPN  m_left,m_right;
            int  m_depth;

            Node(const _T& _val=_T(),
                 FPN _left=FPN(NULL,true),
                 FPN _right=FPN(NULL,true)) 
                : m_value(_val),m_left(_left),m_right(_right) {
                m_depth=1+max(AVLTree::depth(_left),
                              AVLTree::depth(_right));
            }

            ~Node() {
                if(!m_left.flag()) delete m_left.ptr();
                if(!m_right.flag()) delete m_right.ptr();        
            }

        public:
            // Public interface
            FPN left() const {
                return m_left;
            }
            FPN right() const {
                return m_right;
            }

            const _T& value() const {
                return m_value;
            }

            int depth() const {
                return m_depth;
            }
        };

    private:
        // Internal utilities
        static void leftRot(FPN* _root) {
            FlaggedPtr<Node> tmp=*_root;
            *_root=(*_root)->m_right;
            tmp->m_right=(*_root)->m_left.flag()?FPN(*_root,true):(*_root)->m_left;
            (*_root)->m_left=tmp;

            tmp->m_depth=1+max(depth(tmp->m_left),depth(tmp->m_right));
            (*_root)->m_depth=1+max(depth(tmp),depth((*_root)->m_right));
        }
        static void rightRot(FPN* _root) {
            FlaggedPtr<Node> tmp=*_root;
            *_root=(*_root)->m_left;
            tmp->m_left=(*_root)->m_right.flag()?FPN(*_root,true):(*_root)->m_right;
            (*_root)->m_right=tmp;

            tmp->m_depth=1+max(depth(tmp->m_left),depth(tmp->m_right));
            (*_root)->m_depth=1+max(depth((*_root)->m_left),depth(tmp));
        }

        static FPN* leftMost(Node* _root) {
            FPN cur=_root;
            while(!cur->m_left.flag())
                cur=cur->m_left;
            return &cur->m_left;
        }

        static int depth(FPN _root) {
            return (_root.flag()?0:_root->m_depth);
        }
        static int bal(const Node& _root) {
            return depth(_root.m_left)-depth(_root.m_right);
        }

        static bool insert(const _T& _elem,FPN _parent,FPN* _root) {
            if(_root->flag()) {
                if(_root==&(_parent->m_left))
                    *_root=new Node(_elem,FPN(*_root,true),FPN(_parent,true));
                else
                    *_root=new Node(_elem,FPN(_parent,true),FPN(*_root,true));
                _root->setFlag(false);
            }
            else {
                _Less less;

                if(less(_elem,(*_root)->m_value))
                    if(insert(_elem,*_root,&(*_root)->m_left)) {
                        (*_root)->m_depth=1+max(depth((*_root)->m_left),depth((*_root)->m_right));
                        if(bal(**_root)==2) {
                            if(bal(*(*_root)->m_left)==-1)
                                leftRot(&(*_root)->m_left);
                            rightRot(_root);
                        }
                    }
                    else
                        return false;
                else if(less((*_root)->m_value,_elem))
                    if(insert(_elem,*_root,&(*_root)->m_right)) {
                        (*_root)->m_depth=1+max(depth((*_root)->m_left),depth((*_root)->m_right));
                        if(bal(*(*_root))==-2) {
                            if(bal(*(*_root)->m_right)==1)
                                rightRot(&(*_root)->m_right);
                            leftRot(_root);
                        }
                    }
                    else
                        return false;
                else 
                    return false;
            }
            return true;
        }

        static void erase_2(FPN* _cur,FPN* _root) {
            if((*_cur)->m_right.flag()) {
                FPN newRoot=*_cur,tmp;
                if((*_cur)->m_left.flag())
                    _cur->setFlag(true);
                else
                    *_cur=FPN((*_cur)->m_left,false);
                newRoot->m_left=(*_root)->m_left;
                newRoot->m_right=(*_root)->m_right;
                tmp=*_root;
                tmp->m_left.setFlag(true);
                tmp->m_right.setFlag(true);
                *_root=newRoot;
                delete tmp.ptr();
            }
            else {
                erase_2(&(*_cur)->m_right,_root);
                if(bal(**_cur)==2) {
                    if(bal(*(*_cur)->m_left)==-1)
                        leftRot(&(*_cur)->m_left);
                    rightRot(_cur);
                }
            }
        }
        static void erase_1(FPN* _root) {
            if((*_root)->m_left.flag()) {
                if((*_root)->m_right.flag()) {
                    FPN newRoot;
                    _root->setFlag(true);
                    if((*_root)->m_right==NULL || (*_root)->m_right->m_left==*_root)
                        newRoot=(*_root)->m_right;
                    else
                        newRoot=(*_root)->m_left;
                    delete _root->ptr();
                    *_root=newRoot;
                }
                else {
                    FPN tmp=*_root;
                    (*_root)->m_right->m_left=(*_root)->m_left;
                    *_root=(*_root)->m_right;
                    tmp->m_right.setFlag(true);
                    delete tmp.ptr();
                }
            }
            else if((*_root)->m_right.flag()) {
                FPN tmp=*_root;
                (*_root)->m_left->m_right=(*_root)->m_right;
                *_root=(*_root)->m_left;
                tmp->m_left.setFlag(true);
                delete tmp.ptr();
            }
            else {
                if((*_root)->m_left->m_right.flag()) {
                    FPN tmp=(*_root)->m_left;
                    tmp->m_right=(*_root)->m_right;
                    (*_root)->m_right.setFlag(true);
                    (*_root)->m_left.setFlag(true);
                    delete _root->ptr();
                    *_root=tmp;
                }
                else
                    erase_2(&(*_root)->m_left,_root);

                (*_root)->m_depth=1+max(depth((*_root)->m_left),depth((*_root)->m_right));
                if(bal(**_root)==-2) {
                    if(bal(*(*_root)->m_right)==1)
                        rightRot(&(*_root)->m_right);
                    rightRot(_root);
                }
                *leftMost((*_root)->m_right) = FPN(*_root,true);
            }
        }
        static bool erase(const _T& _elem,FPN* _root) {
            if(_root->flag()) return false;

            _Less less;

            if(less(_elem,(*_root)->m_value)) {
                if(erase(_elem,&(*_root)->m_left)) {
                    (*_root)->m_depth=1+max(depth((*_root)->m_left),depth((*_root)->m_right));
                    if(bal(**_root)==-2) {
                        if(bal(*(*_root)->m_right)==1)
                            rightRot(&(*_root)->m_right);
                        leftRot(_root);
                    }
                }
                else
                    return false;
            }
            else if(less((*_root)->m_value,_elem)) {
                if(erase(_elem,&(*_root)->m_right)) {
                    (*_root)->m_depth=1+max(depth((*_root)->m_left),depth((*_root)->m_right));
                    if(bal(**_root)==2) {
                        if(bal(*(*_root)->m_left)==-1)
                            leftRot(&(*_root)->m_left);
                        rightRot(_root);
                    }
                }
                else
                    return false;
            }
            else
                erase_1(_root);

            return true;
        }

        static FPN copyTree(FPN _root,FPN _leftMost,FPN _rightMost) {
            FPN ret=new Node(_root->m_value);

            if(!_root->m_left.flag()) {
                ret->m_left=copyTree(_root->m_left,_leftMost,ret);
                ret->m_left.setFlag(false);
            }
            else 
                ret->m_left=_leftMost.ptr();


            if(!_root->m_right.flag()) { 
                ret->m_right=copyTree(_root->m_right,ret,_rightMost);
                ret->m_right.setFlag(false);
            }
            else
                ret->m_right=_rightMost.ptr();

            return ret;
        }

    private:
        // Properties
        FPN m_root;

    public:
        // Iterator subclass
        class Iterator {
            friend class AVLTree;

        private:
            // Properties
            FPN m_cur;

            Iterator();
            Iterator(FPN _val) : m_cur(_val) {}

        public:
            // Public interface
            const _T& value() const {
                return m_cur->m_value;
            }
            void      forward() {
                m_cur=m_cur->m_right;
                if(!m_cur.flag())
                    while(!m_cur->m_left.flag())
                        m_cur=m_cur->m_left;
            }
            void      backward() {
                m_cur=m_cur->m_left;
                if(!m_cur.flag())
                    while(m_cur->m_right.flag())
                        m_cur=m_cur->m_right;
            }

            bool equal(const Iterator& _other) const {
                return m_cur==_other.m_cur;
            }
            bool NEqual(const Iterator& _other) const {
                return m_cur!=_other.m_cur;
            }

            Iterator& operator++() {
                forward();
                return *this;
            }
            Iterator& operator--() {
                backward();
                return *this;
            }
            const _T& operator*() const {
                return value();
            }
            const _T* operator->() const {
                return m_cur.ptr();
            }

            bool operator==(const Iterator& _other) const {
                return equal(_other);
            }
            bool operator!=(const Iterator& _other) const {
                return NEqual(_other);
            }
        };

    public:
        // Public interface
        AVLTree() : m_root(NULL,true) {}
        AVLTree(const AVLTree& _other) {
            if(_other.empty())
                m_root=FPN(NULL,true);
            else
                m_root=copyTree(_other.m_root,FPN(NULL,true),FPN(NULL,true));
        }

        bool empty() const {
            return m_root.flag();
        }

        FPN  root() const { return m_root; }
        bool insert(const _T& _elem) {
            if(empty()) {
                m_root=new Node(_elem);
                m_root.setFlag(false);

                return true;
            }

            return insert(_elem,m_root,&m_root);
        }
        bool erase(const _T& _elem) {
            return erase(_elem,&m_root);
        }

        Iterator begin() const {
            if(empty()) return end();

            FPN cur=m_root;

            while(!cur->m_left.flag())
                cur=cur->m_left;

            return Iterator(cur);
        }
        Iterator end() const {
            return Iterator(FPN(NULL,true));
        }

        Iterator RBegin() const {
            if(empty()) return REnd();

            FPN cur=m_root;

            while(!cur->m_right.flag())
                cur=cur->m_right;

            return iterator(cur);
        }
        Iterator REnd() const {
            return end();
        }

        ~AVLTree() {
            if(!m_root.flag())
                delete m_root.ptr();
        }
    };
}

#endif // INCLUDED_AVL_TREE_HH
