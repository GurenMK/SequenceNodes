//
// Created by Alexnder Urbanyak on 2/19/2018.
//

#include "sequence3.h"
#include <cassert>
#include <cstdlib>

using namespace std;

namespace main_savitch_5 {

    sequence::sequence() {
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
    }

    sequence::sequence(const sequence& source) {
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        many_nodes = source.many_nodes;

        if (source.many_nodes == 0) {
            head_ptr = NULL;
            tail_ptr = NULL;
            cursor = NULL;
            precursor = NULL;
        }
        else {
            int count = 1;
            node *head = source.head_ptr;
            while (head != NULL && head != source.cursor) {
                count++;
                head = head -> link();
            }
            if(count != 1){
                precursor = list_locate(head_ptr, count - 1);
            }
            cursor = list_locate(head_ptr, count);
        }
    }

    sequence::~sequence() {
        list_clear(head_ptr);
        many_nodes = 0;
    }

    void sequence::start() {
        cursor = head_ptr;
        precursor = NULL;
    }

    void sequence::advance() {
        assert(is_item());

        precursor = cursor;
        cursor = cursor -> link();
    }

    void sequence::insert(const value_type &entry) {
        if (cursor == NULL || cursor == head_ptr) {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
        }
        else {
            node *temp = new node(entry, cursor);
            temp -> set_link(precursor -> link());
            cursor = temp;
            precursor -> set_link(cursor);
            precursor = precursor -> link();
        }
        many_nodes++;
    }

    void sequence::attach(const value_type &entry) {
        if (head_ptr == NULL) {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
        }
        else if (cursor == NULL) {
            list_insert(precursor, entry);
            cursor = precursor -> link();
        }
        else {
            node *temp = new node(entry, cursor -> link());
            cursor -> set_link(temp);
            precursor = cursor;
            cursor = temp;
        }
        many_nodes++;
    }

    void sequence::operator=(const sequence &source) {
        if (this == &source)
            return;

        list_clear(head_ptr);
        many_nodes = 0;
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        many_nodes = source.many_nodes;

        if (source.many_nodes == 0) {
            head_ptr = NULL;
            tail_ptr = NULL;
            cursor = NULL;
            precursor = NULL;
        }
        else {
            int count = 1;
            node *head = source.head_ptr;
            while (head != NULL && head != source.cursor) {
                count++;
                head = head -> link();
            }
            if(count != 1){
                precursor = list_locate(head_ptr, count - 1);
            }
            cursor = list_locate(head_ptr, count);
            tail_ptr = list_locate(head_ptr, many_nodes);
        }
    }

    void sequence::remove_current() {
        assert(is_item());

        if (cursor == head_ptr) {
            cursor = head_ptr -> link();
            list_head_remove(head_ptr);
        }
        else {
            list_remove(precursor);
            cursor = precursor -> link();
        }
        many_nodes--;
    }

    sequence::value_type sequence::current() const{
        assert(is_item());

        return cursor -> data();
    }
}
