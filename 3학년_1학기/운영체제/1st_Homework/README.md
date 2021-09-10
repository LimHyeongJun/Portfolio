## Implementing a Simple Hash Table
* 개발 환경 : C / Ubuntu 18.04 (VMware)
* 전체적인 구조

<kbd><img src = "https://user-images.githubusercontent.com/48857568/132866845-ccf05a74-d567-4326-88cd-44c48bbfebe1.JPG" width="500" height="350"></kbd>

* Problem Description
  * C언어를 이용하여 간단한 Hash Table을 구현해본다
  * 숫자를 저장하는 구조체 `Object`는 아래와 같은 멤버를 갖는다
    * 숫자가 저장되는 `int objnum`
    * 이전의 Object를 가리키는 `Object* phPrev`
    * 다음의 Object를 가리키는 `Object* phNext`
  * Object의 Linked list인 `HashTableEnt`는 아래와 같은 멤버를 갖는다.
    * 몇 개의 Object가 연결되어 있는지 저장하는 `int elmtCount`
    * Linked list의 head를 가리키는 `Object* pHead`
    * Linked list의 tail을 가리키는 `Object* pTail`
  * HashTableEnt를 배열로 갖고 있는 `HashTableEnt pHashTableEnt[8]`
  * Object가 Free 하게 있는 List인 FreeList에 대한 변수는 아래와 같다.
    * FreeList의 head를 가리키는 `Object* pFreeListHead`
    * FreeList의 tail을 가리키는 `Object* ppFreeListTail`
* 구현 함수
  * `void InsertObjectToTail(Object* pObj, int ObjNum)`
    * pHashTableEnt의 `ObjNum % 8` 인덱스에 해당 ObjNum을 갖는 pObj를 Tail 부분에 삽입한다.
  * `void InsertObjectToTail(Object* pObj, int ObjNum)`
    * pHashTableEnt의 `ObjNum % 8` 인덱스에 해당 ObjNum을 갖는 pObj를 Head 부분에 삽입한다.
  * `Object* GetObjectByNum(int objnum)`
    * 성공한다면, objnum을 가진 Object를 찾아서 리턴해준다
    * 실패한다면, NULL을 리턴한다.
    * 성공해서 리턴했을 때, Hash Table에서 해당 Object를 지우면 안 된다.
  * `BOOL DeleteObject(Object* pObj)`
    * 인자로 pObj를 Hash Table에서 찾아 해당 Object를 삭제한다.
    * 만약 성공한다면, TRUE를 리턴한다.
    * 실패한다면, FALSE를 리턴한다. Hash Table에 해당 Object가 없으면 실패한 것이다.
  * `Object* GetObjectFromObjFreeList(void)`
    * FreeList의 Head로부터 새로운 Object를 얻는 함수이다.
    * 성공한다면, 새로운 Object의 포인터를 리턴한다.
    * 실패한다면, NULL을 리턴한다. 실패했다는 의미는 FreeList에 아무 Object도 없다는 뜻이다.
  * `void InsertObjectIntoObjFreeList(Object* pObj)`
    * 인자로 주어진 pObj를 FreeList의 Head로 삽입한다.
