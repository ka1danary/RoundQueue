#include <iostream>

using namespace std;

template <typename T>

class QueueRing
{
private:
    T* queue; // очередь в виде массива
    int count; // текущая длина очереди
    int maxCount; // максимальный размер очереди

    // Метод, осуществляющий копирование очереди
    void Copy(const QueueRing<T>& obj)
    {
        // 1. Освободить память, предварительно выделенную для очереди
        if (maxCount > 0)
            delete[] queue;

        // 2. Скопировать данные
        try
        {
            count = obj.count;
            maxCount = obj.maxCount;

            // выделить память для новой очереди
            queue = new T[maxCount];

            // цикл копирования данных
            for (int i = 0; i < maxCount; i++)
                queue[i] = obj.queue[i];
        }
        catch (bad_alloc e)
        {
            cout << e.what() << endl;
        }
    }

public:
    // Конструктор int
    QueueRing(int _maxCount)
    {
        // Создать очередь размером _maxCount
        try
        {
            maxCount = _maxCount;
            queue = new T[maxCount]; // выделить память для очереди
            count = 0; // пока что очередь пуста
        }
        catch (bad_alloc e)
        {
            cout << e.what() << endl;
        }
    }

    // Конструктор string
    QueueRing(string _maxCount)
    {
        // Создать очередь размером _maxCount
        try
        {
            maxCount = _maxCount;
            queue = new T[maxCount]; // выделить память для очереди
            count = 0; // пока что очередь пуста
        }
        catch (bad_alloc e)
        {
            cout << e.what() << endl;
        }
    }

    // Конструктор копирования
    QueueRing(const QueueRing& obj)
    {
        Copy(obj);
    }

    // Оператор копирования
    QueueRing<T> operator=(const QueueRing& obj)
    {
        Copy(obj);
        return *this;
    }

    // Очистка очереди
    void Clear()
    {
        count = 0;
    }

    // Деструктор
    ~QueueRing()
    {
        if (maxCount > 0)
            delete[] queue; // освободить память, выделенную под очередь
    }

    // Проверка, пуста ли очередь?
    bool isEmpty()
    {
        return count == 0;
    }

    // Получить количество элементов очереди
    int Count()
    {
        return count;
    }

    // Проверка, заполнена ли очередь?
    bool isFull()
    {
        return count == maxCount;
    }

    // Добавить новый элемент в очередь
    void Add(T item)
    {
        if (!isFull()) // если очередь не заполнена
            queue[count++] = item;
    }

    // Вытянуть первый элемент из очереди и поместить в конец очереди
    bool Move()
    {
        if (!isEmpty()) // Если очередь заполнена
        {
            // запомнить первый элемент
            T item = queue[0];

            // сдвиг элементов
            for (int i = 1; i < count; i++)
                queue[i - 1] = queue[i];

            // первый элемент записать в конец очереди
            queue[count - 1] = item;
            return true;
        }
        else
            return false;
    }

    // Вернуть первый элемент очереди 
    string Peek() {
        if (!isEmpty()) {
            T item = queue[0];
            return item;
        }
        else {
            cout << "Очередь пустая" << endl;
            return 0;
        }
    }


    // Метод, выводящий очередь
    void Print(string msg)
    {
        cout << msg + " ";
        for (int i = 0; i < count; i++)
            cout << queue[i] << " ";
        cout << endl;
    }

    
};

void main()
{

    int n, k;
    cout << "Input lenght student  - "; 
    cin >> n;
    cout << endl;

    cout << "Input lenght tickets - ";
    cin >> k;
    cout << endl;

    if (n < 1) {
        cout << "Please, entrance a lenght for students, more 0" << endl;
    }
    if (k < 1) {
        cout << "Please, entrance a lenght for tickets, more 0" << endl;
    }
    

    string* students = new string[20]{ 
        "Mark Ivanov", 
        "Xenia Markova", 
        "Petr Grishkov", 
        "Maria Hoverova", 
        "Elizaveta Nevidimaya", 
        "Rayan Gosling", 
        "Nikita Ivanov", 
        "Alexsey Tor", 
        "Mihail Petrov", 
        "Danil Smolnikov", 
        "Alena Viatkina", 
        "Sergey Domashev", 
        "Victor Nechoroshev", 
        "Kristina Koshel",
        "Stormi Pirkis",
        "Teddy Calken",
        "Brandy Klosa",
        "Aloisia Sieghard",
        "Magdaia Turone",
        "Carling Kerfod"
    };
    string* tickets = new string[14]{ "100", "101", "102", "103", "104", "105", "106", "107", "108", "109", "110", "111", "112", "113" };


    // Пустой список 

    string** list = new string*[n];
    for (int i = 0; i < n; i++) {
        list[i] = new string [2];
    }

    // Создать очередь для билетов
    QueueRing<string> qTickets(k);

    // Создать очередь для студентов
    QueueRing<string> qStudents(n);

    // Заполнить очередь студентов 
    for (int i = 0; i < n; i++) {
        qStudents.Add(students[i]);
    }
    // Заполнить очередь билетов
    for (int i = 0; i < k; i++) {
        qTickets.Add(tickets[i]);
    }

    qTickets.Print("Tickets : ");
    qStudents.Print("Students : ");

    cout << endl;

    // Проходимся по каждому элементу  1 списка - Студенты

    for (int i = 0; i < n; i++) {

        // Проходимся по каждому элементу 2 списка - Билеты
        for (int j = 0; j < 2; j++) {
            if (j == 0) {
                list[i][j] = qStudents.Peek();
               
            }
            else if(j == 1) {
                list[i][j] = qTickets.Peek();
                qStudents.Move();
            }
        }
         qStudents.Move();
         qTickets.Move();
    }

    cout << "Total List:" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            cout << list[i][j] << " ";
        }
        cout << endl;
    }

}