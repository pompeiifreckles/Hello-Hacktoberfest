#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>
#include <exception>
#include <iterator>
#include <string>

namespace selfmade {

class LinkedListException final : public std::exception {
    private:
        std::string mMsg;
    public:
        explicit LinkedListException(const std::string& aMsg): mMsg(aMsg) {
        }

        const char* what() const noexcept override {
            return mMsg.c_str();
        }
};

template<typename type>
class Node {
    private:
        Node<type>* mNext;
        type mData;
    public:
        Node() {
            mNext = nullptr;
        }

        explicit Node(Node<type>* aNext) {
            mNext = aNext;
        }

        Node(Node<type>* aNext, const type& aData) {
            mNext = aNext;
            mData = aData;
        }

        Node<type>* getNext() const {
            return mNext;
        }

        const type& getData() const {
            return mData;
        }

        void setNext(Node<type>* aNext) {
            mNext = aNext;
        }

        void setData(const type& aData) {
            mData = aData;
        }

        void destroy() {
            if (mNext != nullptr) {
                mNext = nullptr;
            }
        }

        ~Node() {
            destroy();
        }
};

template<typename type>
class LinkedList {
    private:
        Node<type>* mHead;
        size_t mSize;

        void destroy() {
            Node<type>* node = mHead;
            Node<type>* temp = nullptr;
            while (node != nullptr) {
                temp = node->getNext();
                delete node;
                node = temp;
            }

            mHead = nullptr;
            mSize = 0;
        }
    public:
        LinkedList() {
            mHead = nullptr;
            mSize = 0;
        }

        ~LinkedList() {
            destroy();
        }

        size_t getSize() const {
            return mSize;
        }

        bool isEmpty() const {
            return mSize == 0;
        }

        const type& operator[](size_t aIndex) const {
            if (aIndex >= mSize) { 
                throw LinkedListException("Index out of range");
            }
            Node<type>* node;
            size_t id = 0;

            for (node = mHead;
                 node->getNext() != nullptr;
                 node = node->getNext(), id++) {
                if (id == aIndex) {
                    break;
                }
            }

            return node->getData(); 
        }

        void insert(size_t aIndex, const type& aObject) {
            if (aIndex >= mSize) { 
                throw LinkedListException("Index out of range");
            }

            if (aIndex == 0) {
                pushFront(aObject);
                return ;
            }

            if (aIndex == mSize) {
                pushBack(aObject);
                return ;
            }

            Node<type>* node = nullptr;
            Node<type>* last = nullptr;
            size_t id = 0;

            for (node = mHead;
                 node->getNext() != nullptr;
                 last = node, node = node->getNext(), id++) {
                if (id == aIndex) {
                    break;
                }
            }

            Node<type>* new_node = new Node<type>(node, aObject);
            last->setNext(new_node);
            mSize++;
        }

        void pushBack(const type& aObject) {
            if (mHead == nullptr) {
                pushFront(aObject);
                return ;
            }

            Node<type>* node = mHead;
            while (node->getNext() != nullptr) {
                node = node->getNext();
            }

            Node<type>* new_node = new Node<type>(nullptr, aObject);
            node->setNext(new_node);
            mSize++;
        }

        void pushFront(const type& aObject) {
            Node<type>* new_node = new Node<type>(mHead, aObject);
            mHead = new_node;
            mSize++;
        }

        void remove(const type& aObject) {

        }

        void erase(size_t aIndex) {
            if (aIndex >= mSize) { 
                throw LinkedListException("Index out of range");
            }

            if (aIndex == 0) {
                popFront();
                return ;
            }

            if (aIndex == mSize - 1) {
                popBack();
                return ;
            }

            Node<type>* node = nullptr;
            Node<type>* last = nullptr;
            size_t id = 0;

            for (node = mHead;
                 node->getNext() != nullptr;
                 last = node, node = node->getNext(), id++) {
                if (id == aIndex) {
                    break;
                }
            }

            last->setNext(node->getNext());
            delete node;
            mSize--;
        }

        type popBack() {
        
        }

        type popFront() {
            Node<type>* node = mHead;
            mHead = mHead->getNext();
            type data = node->getData();
            delete node;
            mSize--;

            return data;
        }

        const type& front() const {
            if (mHead == nullptr) {
                throw LinkedListException("Empty list");
            }

            return mHead->getData();
        }

        const type& back() const {
            if (mHead == nullptr) {
                throw LinkedListException("Empty list");
            }

            Node<type>* node = mHead;
            while (node->getNext() != nullptr) {
                node = node->getNext();
            }

            return node->getData();
        }

        size_t find(const type& aObject) {

        }

        void reverse() {

        }

        class iterator {
            private:
                Node<type>* mNode;

                class NodeHolder {
                    Node<type>* mNode;
                    public:
                        explicit NodeHolder(Node<type>* aNode): mNode(aNode) {}
                        const type& operator*() {
                            return mNode->getData();
                        }
                };
            public:
                typedef Node<type>*             value_type;
                typedef std::ptrdiff_t          difference_type;
                typedef Node<type>**            pointer;
                typedef Node<type>*&            reference;
                typedef std::input_iterator_tag iterator_category;

                iterator() {
                    mNode = nullptr;
                }

                explicit iterator(Node<type>* aNode): mNode(aNode) {}
                
                const type& operator*() const {
                    return mNode->getData();
                }

                bool operator==(const iterator& other) const {
                    return mNode == other.mNode;
                }

                bool operator!=(const iterator& other) const {
                    return mNode != other.mNode;
                }

                NodeHolder operator++(int) {
                    NodeHolder ret(mNode);
                    if (mNode != nullptr) {
                        mNode = mNode->getNext();
                    }
                    return ret;
                }

                iterator& operator++() {
                    if (mNode != nullptr) {
                        mNode = mNode->getNext();
                    }
                    return *this;
                }
        };

        iterator begin() {
            return iterator(mHead);
        }

        iterator end() {
            return iterator(nullptr);
        }
};

} // namespace selfmade

#endif
