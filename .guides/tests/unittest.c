#include <string.h>
#include "narwhal.h"
#include "/home/codio/workspace/list/list.h"
#include <ctype.h>
#include <time.h>

char* list_out(list_t *l);
char* stringToLower(char * str);
void list_printout(list_t *l);
char* itoa(int value, char* result, int base);
char *strremove(char *str, const char *sub);

TEST_FIXTURE(mylist, list_t *)
{
   *mylist = NULL;
   *mylist = list_alloc();
   ASSERT(*mylist != NULL, "list_alloc() failed");

    CLEANUP_FIXTURE(mylist)
    {
        list_free(*mylist);
        CAPTURE_OUTPUT(output)
        {
            list_printout(*mylist);
        }

        ASSERT_SUBSTRING(stringToLower(output), "EMPTY");
    }
    
}

TEST(LIST_ADD_TO_FRONT_EMPTYLIST, mylist)
{
    GET_FIXTURE(mylist);
    list_add_to_front(mylist, 10); 
    CAPTURE_OUTPUT(output)
    {
       list_printout(mylist);
    }

    ASSERT_SUBSTRING(output,"10 ");
}

TEST(LIST_ADD_TO_FRONT_NONEMPTYLIST, mylist)
{
    GET_FIXTURE(mylist);
    list_add_to_front(mylist, 10); 
    list_add_to_front(mylist, 15); 
    list_add_to_front(mylist, 16); 
    CAPTURE_OUTPUT(output)
    {
       list_printout(mylist);
    }

    ASSERT_SUBSTRING(output,"16 15 10 ");
}

TEST(LIST_ADD_TO_BACK_EMPTYLIST, mylist)
{
    GET_FIXTURE(mylist);
    list_add_to_back(mylist, 10); 
    CAPTURE_OUTPUT(output)
    {
       list_printout(mylist);
    }

    ASSERT_SUBSTRING(output,"10 ");
}

TEST(LIST_ADD_TO_BACK_NONEMPTYLIST, mylist)
{
    GET_FIXTURE(mylist);
    list_add_to_back(mylist, 10); 
    list_add_to_back(mylist, 15); 
    list_add_to_back(mylist, 16); 
    CAPTURE_OUTPUT(output)
    {
       list_printout(mylist);
    }

    ASSERT_SUBSTRING(output,"10 15 16 ");
}

TEST(LIST_ADD_TO_ITH_EMPTYLIST, mylist)
{
    GET_FIXTURE(mylist);
    list_add_at_index(mylist, 10, 0);
    list_add_at_index(mylist, 14, 1);
    list_add_at_index(mylist, 13, 1);
    CAPTURE_OUTPUT(output)
    {
       list_printout(mylist);
    }

    ASSERT_SUBSTRING(output,"10 13 14 ");
}

TEST(LIST_ADD_TO_ITH_OUT_OF_RANGE_EMPTYLIST, mylist)
{
    GET_FIXTURE(mylist);
    list_add_at_index(mylist, 10, 100);

    CAPTURE_OUTPUT(output)
    {
       list_printout(mylist);
    }

    ASSERT_SUBSTRING(output,"10 ");
}

TEST(LIST_ADD_TO_ITH_NONEMPTYLIST, mylist)
{
    GET_FIXTURE(mylist);
    list_add_at_index(mylist, 10, 100);
    list_add_at_index(mylist, 15, 100);
    list_add_at_index(mylist, 16, 100);
    list_add_at_index(mylist, 9, 0);
    list_add_at_index(mylist, 12, 2);
    list_add_at_index(mylist, 20, 6);
    CAPTURE_OUTPUT(output)
    {
       list_printout(mylist);
    }

    ASSERT_SUBSTRING(output,"9 10 12 15 16 20 ");
}

TEST(LIST_REMOVE_FROM_FRONT_EMPTYLIST, mylist)
{
    int val;

    GET_FIXTURE(mylist);
    val = list_remove_from_front(mylist);
    ASSERT_EQ(val,-1);
}

TEST(LIST_REMOVE_FROM_FRONT_NONEMPTYLIST, mylist)
{
    int val;

    GET_FIXTURE(mylist);
    list_add_to_front(mylist, 10); 
    list_add_to_front(mylist, 15); 
    list_add_to_front(mylist, 16); 
    val = list_remove_from_front(mylist);
    CAPTURE_OUTPUT(output)
    {
       list_printout(mylist);
    }

    ASSERT_SUBSTRING(output,"15 10 ");
    ASSERT_EQ(val,16);
}

TEST(LIST_REMOVE_FROM_BACK_EMPTYLIST, mylist)
{
    int val;

    GET_FIXTURE(mylist);
    val = list_remove_from_back(mylist);
    ASSERT_EQ(val,-1);
}

TEST(LIST_REMOVE_FROM_BACK_NONEMPTYLIST, mylist)
{
    int val;

    GET_FIXTURE(mylist);
    list_add_to_front(mylist, 10); 
    list_add_to_front(mylist, 15); 
    list_add_to_front(mylist, 16); 
    val = list_remove_from_back(mylist);
    CAPTURE_OUTPUT(output)
    {
       list_printout(mylist);
    }

    ASSERT_SUBSTRING(output,"16 15 ");
    ASSERT_EQ(val,10);
}

TEST(LIST_REMOVE_FROM_ITH_EMPTYLIST, mylist)
{
    int val;

    GET_FIXTURE(mylist);

    val = list_remove_at_index(mylist, 1);

    ASSERT_EQ(val, -1);
}

TEST(LIST_REMOVE_FROM_ITH_OUT_OF_RANGE, mylist)
{
    int val;

    GET_FIXTURE(mylist);
    list_add_to_front(mylist, 10); 
    list_add_to_front(mylist, 15); 
    list_add_to_front(mylist, 16); 
   
    val = list_remove_at_index(mylist, 100);

    ASSERT_EQ(val, -1);
}

TEST(LIST_REMOVE_FROM_ITH_NONEMPTYLIST, mylist)
{
    int val;

    GET_FIXTURE(mylist);
    list_add_to_front(mylist, 10); 
    list_add_to_front(mylist, 15); 
    list_add_to_front(mylist, 16); 

    val = list_remove_at_index(mylist, 1);
    CAPTURE_OUTPUT(output)
    {
       list_printout(mylist);
    }

    ASSERT_SUBSTRING(output,"16 10 ");
}

TEST(SEARCH_NONEMPTYLIST, mylist)
{
    int val, i;
    bool retval;

    GET_FIXTURE(mylist);

    for(i = 0; i < 100; i++)
         list_add_to_front(mylist, i); 

    // RANDOM
    retval =  list_is_in(mylist, 9);
    ASSERT_EQ(retval,true);

    // FRONT
    retval =  list_is_in(mylist, 0);
    ASSERT_EQ(retval,true);

    // BACK
    retval =  list_is_in(mylist, 99);
    ASSERT_EQ(retval,true);

    // NOT IN LIST
    retval =  list_is_in(mylist, 180);
    ASSERT_EQ(retval,false);
}

TEST(FINDING_BY_INDEX_NONEMPTYLIST, mylist)
{
    int val, i;
    int retval;

    GET_FIXTURE(mylist);

    for(i = 0; i < 100; i++)
         list_add_to_back(mylist, i); 

    // RANDOM
    retval =  list_get_index_of(mylist, 21);
    ASSERT_EQ(retval,21);

    // FRONT
    retval =  list_get_index_of(mylist, 0);
    ASSERT_EQ(retval,0);

    // BACK
    retval =  list_get_index_of(mylist, 99);
    ASSERT_EQ(retval,99);

    // NOT IN LIST
    retval =  list_get_index_of(mylist, -999999);
    ASSERT_EQ(retval,-1);
}
	
TEST(RETURN_ELEM_BY_INDEX_EMPTYLIST, mylist)
{
    int val, i;
    int retval;

    GET_FIXTURE(mylist);

    // RANDOM
    retval =  list_get_elem_at(mylist, 90);
    ASSERT_EQ(retval,-1);
}

TEST(RETURN_ELEM_BY_INDEX_NONEMPTYLIST, mylist)
{
    int val, i;
    int retval;

    GET_FIXTURE(mylist);

    for(i = 0; i < 100; i++)
         list_add_to_back(mylist, i); 

    // RANDOM
    retval =  list_get_elem_at(mylist, 30);
    ASSERT_EQ(retval,30);

    // FRONT
    retval =  list_get_elem_at(mylist, 0);
    ASSERT_EQ(retval,0);

    // BACK
    retval =  list_get_elem_at(mylist, 99);
    ASSERT_EQ(retval,99);

    // NOT IN LIST
    retval =  list_get_elem_at(mylist, -999999);
    ASSERT_EQ(retval,-1);
}

TEST(RANDOM_TESTS, mylist)
{
  int i, j, val;
  int randloc;
  char buf[1000 *6], tbuf[1000 *6], t2buf[10];
  char* token;
  char tmp[20];
  time_t t;
  int N = 20;

  srand((unsigned) time(&t));

  GET_FIXTURE(mylist);

  for(i = 0; i < N; i++)
  {
    switch(rand() % 3)
    {
       case 0:
               list_add_to_back(mylist, i);

               itoa(i,tmp,10);
               strcat(buf, tmp);
               strcat(buf, " ");
               break;
       case 1:
               list_add_to_front(mylist, i);

               itoa(i,tbuf,10);
               strcat(tbuf, " ");
               strcat(tbuf, buf);
               strcpy(buf, tbuf);

               break;
       case 2: 
               j = 0;
               randloc = rand() % N;
               list_add_at_index(mylist, i, randloc); 

               if(list_length(mylist) <= 0)
               {
                memset(tbuf,0,1000 *6);
                itoa(i,tbuf,10);
                strcat(tbuf, " ");
                strcat(tbuf, buf);
                strcpy(buf, tbuf);
               }
               else 
               {
                token = strtok(buf, " ");
                memset(tbuf,0,1000 *6);
                while (token != NULL) {
                  
                  if(j == randloc)
                  {
                    itoa(i,t2buf,10);
                    strcat(t2buf, " ");
                    strcat(tbuf, t2buf);
                    j++;
                  }
                  strcat(tbuf, token);
                  strcat(tbuf, " ");
                  j++;

                  token = strtok(NULL, " ");
                }
               

                 if(j <= randloc)
                 {
                    itoa(i,t2buf,10);
                    strcat(t2buf, " ");
                    strcat(tbuf, t2buf);
                 }
               
               }
               strcpy(buf, tbuf);
               break;
            /*
      case 3:  
               randloc = rand() % i;
               val = list_remove_at_index(mylist, randloc);
               memset(tbuf,0,1000 *6);
               memset(t2buf,0,10);
               if( val != -1) {
                  itoa(val,t2buf,10);
                  printf("[BUFF = %s]", buf);
                  token = strtok(buf, " ");
                  while (token != NULL) {
                      printf(" IS[%s != %s]", token, t2buf);
                      if(strcmp(token, t2buf) != 0) {
                           strcat(tbuf, token);
                           strcat(tbuf, " "); 
                           printf(" Y[%s]", tbuf);
                      }
                      token = strtok(NULL, " ");
                  }
                  printf("[TBUFF = %s]", tbuf);
                  strcpy(buf, tbuf);
               }
               break;
               
      case 4:
               randloc = rand() % i;
               val = list_remove_from_front(mylist);
               memset(tbuf,0,1000 *6);
               if( val != -1) {
                  itoa(val,tbuf,10);
                  strcat(tbuf, " ");
                  strremove(buf, tbuf);
               }
               break;
      case 5:
               randloc = rand() % i;
               val = list_remove_from_back(mylist);
               memset(tbuf,0,1000 *6);
               if( val != -1) {
                  itoa(val,tbuf,10);
                  strcat(tbuf, " ");
                  strremove(buf, tbuf);
               }
               break;
               */
    }

    CAPTURE_OUTPUT(output)
    {
      list_printout(mylist);
    }

    ASSERT_SUBSTRING(output, (char *)buf);
    
  }
}

char *strremove(char *str, const char *sub) {
    char *p, *q, *r;
    if (*sub && (q = r = strstr(str, sub)) != NULL) {
        size_t len = strlen(sub);
        while ((r = strstr(p = r + len, sub)) != NULL) {
            memmove(q, p, r - p);
            q += r - p;
        }
        memmove(q, p, strlen(p) + 1);
    }
    return str;
}

char* stringToLower(char * str)
{
  int j = 0;
      while (str[j]) {

        str[j] = toupper(str[j]);
        j++;
     }
  
  return str;
}

void list_printout(list_t *l) 
{
  node_t *current = l->head;
  elem v;

  if (current == NULL){
    printf("list is empty\n");
  }
  while (current != NULL){
    v = current->value;
    printf("%d ", v);
    current = current->next;
  }
}

char* itoa(int value, char* result, int base) {
    snprintf(result, base, "%d", value);
    /*
		// check that the base if valid
		if (base < 2 || base > 36) { *result = '\0'; return result; }

		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;

		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );

		// Apply negative sign
		if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
        */
		return result;
        
	}
