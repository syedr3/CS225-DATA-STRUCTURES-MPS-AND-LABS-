/* Your code here! */
#include <dsets.h>
void DisjointSets::addelements(int num){ //Just keep on adding the number of elements you want with each of size "1".
while (num != 0){
    hey.push_back(-1);
    num--;
}
}


int DisjointSets::find(int elem){//Keep on going up the tree until you find the parent.
    // int found;
    // int ahead;
    // found = elem;
    // ahead = hey[found];
    // while (ahead >= 0){
    //     found = ahead;
    //     ahead = hey[ahead];
    // }
    // return found;
    if (hey[elem] < 0) {return elem;}
    int found = find(hey[elem]);
    hey[elem] = found;
    return found;
}


void DisjointSets::setunion	(int a,int b){ //
int first_guy = size(a);
int first_guy_dad = find(a);
int second_guy = size(b);
int second_guy_dad = find(b);
int final_size = first_guy + second_guy;
if (first_guy > second_guy){
    hey[second_guy_dad] = first_guy_dad;
    hey[first_guy_dad] = -final_size;
}
else{
    hey[first_guy_dad] = second_guy_dad;
    hey[second_guy_dad] = -final_size;
}

}

int DisjointSets::size	(int elem)	{ //Keep on going up until the parent points at the negation of it's size, and then negate the negation to get the size.
    // while (elem >= 0){
    //     elem = hey[elem];
    // }
    // elem = -elem;
    // return elem;
    elem = find(elem);
    return -hey[elem];
}