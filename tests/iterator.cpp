

// input_iterator = *it it++ ++it it!=it it==it
// output_iterator = *it=val it++ ++it it!=it it==it
// forward_iterator = *it *it=val it++ ++it it!=it it==it
// bidirectional_iterator = *it *it=val it++ ++it it!=it it==it it-- --it
// random_access_iterator = *it *it=val it[] it[]=val it++ ++it it!=it it==it it-- --it it+=n it-=n it+n it-n


struct Node {
    Node* m_next;
    int m_value;
};

struct iterator {
    Node* m_curr;

    iterator &operator++() {
        m_curr = m_curr->m_next;
        return *this;
    }


};