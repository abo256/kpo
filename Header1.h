
using namespace std;

struct Settings {
    string specialty = "ПО";       // Значения по умолчанию
    string studentName = "Студент";
    int subjectsCount = 5;
};

// Игровая инфа
class Subject {
private:
    string name;
    int knowledge;      // Уровень знаний по предмету (0-100)
    int attendance;     // Кол-во посещённых пар
    string question;    // Вопрос на экзамене
    string answer;      // Правильный ответ (в нижнем регистре)
    int examGrade;      // Оценка за экзамен
    int labsCompleted;  // Кол-во сданных лабораторных работ
    int midTermGrade;   // Оценка за последнюю промежуточную аттестацию (0-10)
public:
    Subject(string n = "Предмет", string q = "2 + 2 = ?", string a = "4") // На случай если предмет/экзамен/ответ выведется без параметра
        : name(n), knowledge(10), attendance(0), question(q), answer(a),
        examGrade(0), labsCompleted(0), midTermGrade(0) {
    }
    string getName() const { // Чтение данных при помощи геттеров
        return name;
    }
    int getKnowledge() const {
        return knowledge;
    }
    int getAttendance() const {
        return attendance;
    }
    string getQuestion() const {
        return question;
    }
    string getAnswer() const {
        return answer;
    }
    int getExamGrade() const {
        return examGrade;
    }
    int getLabsCompleted() const {
        return labsCompleted;
    }
    int getMidTermGrade() const {
        return midTermGrade;
    }

    void setKnowledge(int k) { // Запись данных с помощью сеттеров
        knowledge = max(0, min(100, k));
    }
    void setAttendance(int a) {
        attendance = max(0, a);
    }
    void setExamGrade(int g) {
        examGrade = g;
    }
    void setLabsCompleted(int l) {
        labsCompleted = max(0, l);
    }
    void setMidTermGrade(int m) {
        midTermGrade = max(0, min(10, m));
    }

    void attendLecture(int bonusKnowledge) {
        attendance++;
        knowledge = min(100, knowledge + 12 + bonusKnowledge);
    }
    void studySelf(int bonusKnowledge) {
        knowledge = min(100, knowledge + 15 + bonusKnowledge);
    }
    void solveTasks(int bonusKnowledge) {
        knowledge = min(100, knowledge + 22 + bonusKnowledge);
    }


    int passLab() { // Сдача лабы в зависимости от знаний на данный момент
        int grade = max(2, min(10, (knowledge / 10) + (rand() % 2)));
        if (grade >= 4) {
            labsCompleted++;
            knowledge = min(100, knowledge + 5);
        }
        return grade;
    }


    int passAttestation() {  // Аттестация
        double score = (knowledge / 100.0) * 7.0 + min(2.0, attendance * 0.5) + min(1.0, labsCompleted * 0.5);
        midTermGrade = max(1, min(10, static_cast<int>(score + 0.5)));
        return midTermGrade;
    }

    bool checkAnswer(string userAnswer) const { // Проверка ответа
        for (char& c : userAnswer) {
            if (c >= 'A' && c <= 'Z') c += 32;
            if (c >= 'А' && c <= 'Я') c += 32;
            if (c == 'Ё') c = 'ё';
        }
        return userAnswer.find(answer) != string::npos;
    }
};

class Student { // Игровая инфа о студенте
private:
    string name;
    string specialty;
    int energy;             // Энергия (0-100)
    int mood;               // Настроение (0-100)
    int baseIntellect;      // Общий интеллект (0-100)
    int money;              // Текущий баланс 
    int monthlyIncome;      // Ежемесячный доход
public:
    Student(string n = "Студент", string spec = "ПО")
        : name(n), specialty(spec), energy(80), mood(80), baseIntellect(10),
        money(200), monthlyIncome(250) {
    }
    string getName() const {
        return name;
    }
    string getSpecialty() const {
        return specialty;
    }
    int getEnergy() const {
        return energy;
    }
    int getMood() const {
        return mood;
    }
    int getIntellect() const {
        return baseIntellect;
    }
    int getMoney() const {
        return money;
    }
    int getMonthlyIncome() const {
        return monthlyIncome;
    }

    void setStats(int en, int md, int intl, int mn = 200, int inc = 250) {
        energy = max(0, min(100, en));
        mood = max(0, min(100, md));
        baseIntellect = max(0, min(100, intl));
        money = max(0, mn);
        monthlyIncome = max(50, inc);
    }
    void changeEnergy(int delta) { energy = max(0, min(100, energy + delta)); }
    void changeMood(int delta) { mood = max(0, min(100, mood + delta)); }
    void changeIntellect(int delta) { baseIntellect = max(0, min(100, baseIntellect + delta)); }
    void changeMoney(int delta) { money = max(0, money + delta); }

    // Перерасчет ежемесячного дохода на основе успеваемости
    void recalculateIncome(double avgAttestationGrade) {
        int baseIncome = 250; // Базовая выплата
        if (avgAttestationGrade >= 8.0) {
            monthlyIncome = baseIncome + 100; // Повышенная стипендия
        }
        else if (avgAttestationGrade >= 6.0) {
            monthlyIncome = baseIncome;       // Обычная выплата
        }
        else if (avgAttestationGrade >= 4.0) {
            monthlyIncome = baseIncome - 80;  // Сниженная выплата из-за низких баллов
        }
        else {
            monthlyIncome = 80;               // Лишение стипендии (остаются только карманные)
        }
    }

    void receiveMonthlyAllowance() {
        money += monthlyIncome;
        cout << "\n Начислены ежемесячные средства: +" << monthlyIncome << " руб.!\n";
        cout << " Текущий баланс: " << money << " руб.\n";
    }

    void printStatus() const {
        cout << "--------------------------------------------------\n";
        cout << "Студент: " << name << " | Специальность: " << specialty << "\n";
        cout << "Энергия: " << energy << "/100 | Настроение: " << mood
            << "/100 | Навык учёбы: " << baseIntellect << "/100\n";
        cout << "Баланс: " << money << " руб. | Ежемесячный доход: " << monthlyIncome << " руб.\n";
        cout << "--------------------------------------------------\n";
    }
};

enum class ActionType {
    ATTEND_CLASS,   // Посетить пару
    SKIP_CLASS,     // Прогулять пару (требует денег)
    STUDY_HOME,     // Почитать конспекты дома
    SOLVE_TASKS,    // Решать практические задачи
    REST,           // Отдохнуть / поспать
    BUY_COFFEE      // Купить кофе и перекус (восстанавливает энергию за деньги)
};

class Action {
private:
    string title;
    ActionType type;
public:
    Action(string t, ActionType tp) : title(t), type(tp) {}
    string getTitle() const { 
        return title; 
    }
    void execute(Student& student, Subject* subject = nullptr) const {
        int bonus = student.getIntellect() / 15;
        switch (type) {
        case ActionType::ATTEND_CLASS:
            if (student.getEnergy() < 15) {
                cout << "Слишком мало энергии. Вы уснули на паре, так ничего не усвоив\n";
                if (subject) subject->attendLecture(0);
                student.changeEnergy(-5);
                student.changeMood(-10);
            }
            else {
                cout << "Вы посетили пару по предмету \"" << subject->getName() << "\".\n";
                if (subject) subject->attendLecture(bonus);
                student.changeEnergy(-15);
                student.changeMood(-5);
                student.changeIntellect(3);
                // Небольшой расход на проезд и обед в столовой
                if (student.getMoney() >= 10) {
                    student.changeMoney(-10);
                    cout << "Потрачено 10 руб. на проезд и обед в столовой.\n";
                }
            }
            break;
        case ActionType::SKIP_CLASS:
            if (student.getMoney() >= 30) {
                cout << "Вы прогуляли пару по предмету \"" << subject->getName() << "\" и погуляли по городу (-30 руб.).\n";
                student.changeMoney(-30);
                student.changeEnergy(15);
                student.changeMood(20);
            }
            else {
                cout << "Денег на прогулку нет, пришлось просто сидеть в своей комнате\n";
                student.changeEnergy(10);
                student.changeMood(5);
            }
            break;
        case ActionType::STUDY_HOME:
            if (student.getEnergy() < 20) {
                cout << "Вы слишком устали для теории. Отдохните\n";
                student.changeMood(-10);
            }
            else {
                cout << "Вы разобрали теорию по предмету \"" << subject->getName() << "\".\n";
                if (subject) subject->studySelf(bonus);
                student.changeEnergy(-20);
                student.changeMood(-5);
                student.changeIntellect(4);
            }
            break;
        case ActionType::SOLVE_TASKS:
            if (student.getEnergy() < 25) {
                cout << "Не хватает сил на практические задачи\n";
                student.changeMood(-12);
            }
            else {
                cout << "Вы успешно сделали практические задачи по предмету \"" << subject->getName() << "\".\n";
                if (subject) subject->solveTasks(bonus);
                student.changeEnergy(-25);
                student.changeMood(-8);
                student.changeIntellect(6);
            }
            break;
        case ActionType::REST:
            cout << "Вы хорошо отдохнули и выспались\n";
            student.changeEnergy(40);
            student.changeMood(25);
            break;
        case ActionType::BUY_COFFEE:
            if (student.getMoney() >= 25) {
                cout << "Вы заказали кофе с десертом (-25 руб.). Бодрость и настроение выросли\n";
                student.changeMoney(-25);
                student.changeEnergy(30);
                student.changeMood(20);
            }
            else {
                cout << "Недостаточно средств (нужно 25 руб.). Пришлось обойтись\n";
                student.changeMood(-5);
            }
            break;
        }
    }
};


void saveSettings(const Settings& s) {
    ofstream fout("settings.txt");
    if (fout.is_open()) {
        fout << s.specialty << "\n";
        fout << s.studentName << "\n";
        fout << s.subjectsCount << "\n";
        fout.close();
    }
    else {
        cout << "Ошибка открытия файла для записи настроек\n";
    }
}

void loadSettings(Settings& s) {
    ifstream fin("settings.txt");
    if (fin.is_open()) {
        getline(fin, s.specialty);
        getline(fin, s.studentName);
        fin >> s.subjectsCount;
        fin.close();
    }
    else {
        saveSettings(s);
    }
}

void loadSpecialties(set<string>& specialties) {
    ifstream fin("specialties.txt");
    if (fin.is_open()) {
        string line;
        while (getline(fin, line)) {
            if (!line.empty()) {
                specialties.insert(line);
            }
        }
        fin.close();
    }
    else {
        specialties = { "ПО", "ИИ", "АСОИ", "КС" };
        ofstream fout("specialties.txt");
        if (fout.is_open()) {
            for (const auto& spec : specialties) {
                fout << spec << "\n";
            }
            fout.close();
        }
    }
}

void saveStudentNames(const list<string>& names) {
    ofstream fout("students.txt");
    if (fout.is_open()) {
        for (const auto& name : names) {
            fout << name << "\n";
        }
        fout.close();
    }
}

void loadStudentNames(list<string>& names) {
    ifstream fin("students.txt");
    if (fin.is_open()) {
        string line;
        while (getline(fin, line)) {
            if (!line.empty()) {
                names.push_back(line);
            }
        }
        fin.close();
    }
}

void StopCls() {
    system("pause");
    system("cls");
}

void printCurrentSettings(const Settings& s) {
    cout << "\nТекущие значения:\n";
    cout << "  Специальность    : " << (s.specialty.empty() ? "(не задана)" : s.specialty) << "\n";
    cout << "  Имя студента     : " << (s.studentName.empty() ? "(не задано)" : s.studentName) << "\n";
    cout << "  Кол-во предметов : " << (s.subjectsCount == 0 ? "(не задано)" : to_string(s.subjectsCount)) << "\n";
}

void settingsMenu(Settings& s, const set<string>& specialties, list<string>& studentNames) {
    int choice1 = 0;
    while (true) {
        cout << "\nНастройки\n";
        printCurrentSettings(s);
        cout << "\n1. Выбрать специальность\n";
        cout << "2. Ввести имя студента\n";
        cout << "3. Задать количество предметов\n";
        cout << "0. Назад в главное меню\n";
        cin >> choice1;
        switch (choice1) {
        case 1: {
            cout << "\nДоступные специальности:\n";
            int idx = 1;
            for (const auto& spec : specialties) {
                cout << "  " << idx++ << ". " << spec << "\n";
            }
            cout << "Введите специальность (или ее номер): ";
            cin.ignore();
            string input;
            getline(cin, input);
            bool foundByNumber = false;
            try {
                int specNum = stoi(input);
                if (specNum >= 1 && specNum <= static_cast<int>(specialties.size())) {
                    auto it = specialties.begin();
                    advance(it, specNum - 1);
                    s.specialty = *it;
                    foundByNumber = true;
                }
            }
            catch (...) {
            }
            if (!foundByNumber) {
                if (specialties.find(input) != specialties.end()) {
                    s.specialty = input;
                }
                else {
                    cout << "Специальность не найдена в списке доступных! Оставлено текущее значение.\n";
                    break;
                }
            }
            saveSettings(s);
            cout << "Сохранено.\n";
            break;
        }
        case 2: {
            if (!studentNames.empty()) {
                cout << "\nРанее заданные имена студентов:\n";
                for (const auto& name : studentNames) {
                    cout << "  - " << name << "\n";
                }
            }
            cout << "Введите имя студента: ";
            cin.ignore();
            getline(cin, s.studentName);
            bool exists = false;
            for (const auto& name : studentNames) { // Проходится по элементам контейнера и проверяет существует ли имя
                if (name == s.studentName) {
                    exists = true;
                    break;
                }
            }
            if (!exists && !s.studentName.empty()) { // Если не существует и не введена пустая строка - записывает новое имя
                studentNames.push_back(s.studentName);
                saveStudentNames(studentNames);
            }
            saveSettings(s);
            cout << "Сохранено.\n";
            break;
        }
        case 3:
            cout << "Введите количество предметов : ";
            cin >> s.subjectsCount;
            if (s.subjectsCount < 1) s.subjectsCount = 1;
            saveSettings(s);
            cout << "Сохранено.\n";
            break;
        case 0:
            StopCls();
            return;
        }
    }
}
void about() {
    cout << "\nО программе\n";
    cout << "v. 0.5, by Bairak Anastasiya \n";
    StopCls();
}

vector<Subject> generateSubjects(const Settings& s) { // Функции игры. Также сессионные вопросы/ответы для предметов
    vector<Subject> pool;
    if (s.specialty == "ПО") {
        pool = {
            Subject("Конструирование ПО", "Какой модификатор доступа скрывает поля класса в C++? (private/public)", "private"),
            Subject("Алгоритмы и структуры данных", "Какова сложность бинарного поиска в отсортированном массиве? (O(log n) / O(n))", "O(log n)"),
            Subject("Базы данных", "Процесс организации данных в базе таким образом, чтобы уменьшить их избыточность и обеспечить целостность это - (нормализация/эквализация)", "нормализация"),
            Subject("Операционные системы", "Как называется ядро ОС Linux? (linux/windows)", "linux"),
            Subject("Дискретная математика", "Сколько вершин у полного графа K4? (4/5)", "4"),
            Subject("Компьютерные сети", "Какой протокол отвечает за надёжную доставку пакетов? (TCP/UDP)", "tcp"),
            Subject("Веб-технологии", "Какой язык используется для разметки веб-страниц? (html/java)", "html")
        };
    }
    else if (s.specialty == "ИИ") {
        pool = {
            Subject("Машинное обучение", "Как называется обучение модели на размеченных данных? (с учителем / без учителя)", "с учителем"),
            Subject("Нейронные сети", "Какая функция активации обычно используется в скрытых слоях нейронных сетей? (ReLU/Sigmoid)", "ReLU"),
            Subject("Теория вероятностей", "Чему равна сумма вероятностей всех элементарных исходов? (0/1)", "1"),
            Subject("Линейная алгебра", "Как называется матрица с единицами на главной диагонали? (единичная/диагональная)", "единичная"),
            Subject("Анализ данных", "Какая популярная библиотека Python используется для работы с таблицами? (pandas/numpy)", "pandas"),
            Subject("Логическое программирование", "Какой язык является классическим для логического программирования? (Prolog/C)", "prolog")
        };
    }
    else if (s.specialty == "АСОИ") {
        pool = {
            Subject("Архитектура ЭВМ", "Какое устройство выполняет арифметические и логические операции? (АЛУ/ОЗУ)", "алу"),
            Subject("Микропроцессорные системы", "В какой системе счисления работает процессор? (двоичной/восьмиричной)", "двоичной"),
            Subject("Схемотехника", "Какой логический элемент выдаёт 1 только когда оба входа равны 1? (И/ИЛИ)", "и"),
            Subject("Системы управления", "Как расшифровывается АСУ? (Автоматически-системный учёт/Автоматизированная система управления", "автоматизированная система управления)"),
            Subject("Защита информации", "Как называется процесс преобразования данных в шифр? (кодирование/шифрование)", "шифрование")
        };
    }
    else {
        pool = {
            Subject("Компьютерная схемотехника и архитектура компьютера", "Набор проводников, связывающий процессор с памятью и устройствами ввода-вывода - это (Плата/Шина)", "шина"),
            Subject("Периферийное оборудование и интерфейсы", "Какое разрешение сканера является самым важным? (Оптическое/HD)", "оптическое"),
            Subject("Проектирование цифровых устройств", "Триггер с разделенными установочными входами это (D/RS)", "RS"),
            Subject("Компьютерные сети и телекоммуникации", "Аббревиатура для персональной сети это (PAN/LAN)", "pan"),
            Subject("Микропроцессорные системы и контроллеры", "Центральное устройство вычислительной системы, выполненное на одной или нескольких больших интегральных схемах это (процессор/ОЗУ)", "процессор")
        };
    }
    int count = max(1, s.subjectsCount);
    vector<Subject> result;
    for (int i = 0; i < count; ++i) {
        if (i < static_cast<int>(pool.size())) {
            result.push_back(pool[i]);
        }
        else {
            result.push_back(Subject("Спецкурс #" + to_string(i + 1) + " (" + s.specialty + ")", // Спецкурсы это доп. предметы на случай если человек выбрал больше чем есть основных
                "Сколько килобайт в одном мегабайте?", "1024"));
        }
    }
    return result;
}

vector<string> splitLine(const string& str, char delimiter) { // Ф-ция для "разрезки" строк по разделителю
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


void saveGameProgress(const Student& student, const vector<Subject>& subjects, int currentDay, int totalDays, const string& filename = "savegame.txt", bool isAutoSave = false) { // Сохранение прогресса 
    const char DELIM = ';';
    ofstream fout(filename);
    if (!fout.is_open()) {
        if (!isAutoSave) cout << "Не удалось сохранить игру в файл " << filename << "!\n";
        return;
    }
    // запись через разделитель (т.е. DELIMeter)
    fout << student.getName() << DELIM << student.getSpecialty() << DELIM << student.getEnergy() << DELIM << student.getMood() << DELIM << student.getIntellect() << DELIM << student.getMoney() << DELIM << student.getMonthlyIncome() << DELIM << currentDay << DELIM << totalDays << DELIM << subjects.size() << "\n";
    for (const auto& subj : subjects) {
        fout << subj.getName() << DELIM << subj.getKnowledge() << DELIM << subj.getAttendance() << DELIM << subj.getQuestion() << DELIM << subj.getAnswer() << DELIM << subj.getExamGrade() << DELIM << subj.getLabsCompleted() << DELIM << subj.getMidTermGrade() << "\n";
    }
    fout.close();
    if (isAutoSave) {
        cout << "| Автосохранение выполнено |\n";
    }
    else {
        cout << "Игра успешно сохранена\n";
    }
}

bool loadGameFromFile(const string& filename, Student& student, vector<Subject>& subjects, int& currentDay, int& totalDays) {
    const char DELIM = ';';
    ifstream fin(filename);
    if (!fin.is_open()) {
        return false;
    }
    string headerLine;
    if (!getline(fin, headerLine) || headerLine.empty()) {
        fin.close();
        return false;
    }
    vector<string> headerParts = splitLine(headerLine, DELIM); // Разделение строки по символу
    if (headerParts.size() < 10) {
        fin.close();
        return false;
    }
    string name = headerParts[0]; // Чтение характеристик
    string spec = headerParts[1];
    int en = stoi(headerParts[2]); // Преобразование из стринг в инт
    int md = stoi(headerParts[3]);
    int intl = stoi(headerParts[4]);
    int mn = stoi(headerParts[5]);
    int inc = stoi(headerParts[6]);
    currentDay = stoi(headerParts[7]);
    totalDays = stoi(headerParts[8]);
    int subjCount = stoi(headerParts[9]);

    student = Student(name, spec); // Создает студента
    student.setStats(en, md, intl, mn, inc);
    subjects.clear();
    for (int i = 0; i < subjCount; ++i) {
        string subjLine;
        if (!getline(fin, subjLine)) break;
        vector<string> subjParts = splitLine(subjLine, DELIM);
        if (subjParts.size() >= 8) {
            Subject subj(subjParts[0], subjParts[3], subjParts[4]);
            subj.setKnowledge(stoi(subjParts[1]));
            subj.setAttendance(stoi(subjParts[2]));
            subj.setExamGrade(stoi(subjParts[5]));
            subj.setLabsCompleted(stoi(subjParts[6]));
            subj.setMidTermGrade(stoi(subjParts[7]));
            subjects.push_back(subj);
        }
    }
    fin.close();
    return !subjects.empty();
}

// Промежуточная аттестация. Влияет на выплаты
void runMidTermAttestation(Student& student, vector<Subject>& subjects) {
    cout << "        ПРОМЕЖУТОЧНАЯ АТТЕСТАЦИЯ\n";
    double totalScore = 0.0;
    for (auto& subj : subjects) {
        int grade = subj.passAttestation();
        totalScore += grade;
        cout << "  - " << subj.getName() << ": оценка " << grade << "/10 "<< (grade >= 4 ? "(Аттестован)" : "(НЕ АТТЕСТОВАН!)") << "\n";
    }
    double avgGrade = totalScore / subjects.size();
    int oldIncome = student.getMonthlyIncome();
    student.recalculateIncome(avgGrade);
    int newIncome = student.getMonthlyIncome();
    cout << "\nСредний балл аттестации: " << avgGrade << "\n";
    if (newIncome < oldIncome) {
        cout << "[ВНИМАНИЕ] Из-за низких оценок ваш ежемесячный доход снижен с "<< oldIncome << " до " << newIncome << " руб.!\n";
        student.changeMood(-15);
    }
    else if (newIncome > oldIncome) {
        cout << "[ОТЛИЧНО] За высокую успеваемость ваша стипендия повышена с " << oldIncome << " до " << newIncome << " руб.!\n";
        student.changeMood(15);
    }
    else {
        cout << "Ваш ежемесячный доход остался прежним: " << newIncome << " руб.\n";
    }
    cout << "==================================================\n";
}

// Проведение экзаменационной сессии
void runSession(Student& student, vector<Subject>& subjects) {
    system("cls");
    cout << "               НАЧАЛАСЬ СЕССИЯ!\n";
    student.printStatus();
    cout << "Итоговая оценка зависит от знаний, посещаемости, сданных лабораторных, состояния и ответа на вопрос.\n\n";
    int passedCount = 0;
    double sumGrades = 0.0;
    for (size_t i = 0; i < subjects.size(); ++i) {
        cout << "\n--- Экзамен " << (i + 1) << " из " << subjects.size() << ": " << subjects[i].getName() << " ---\n";
        cout << "Знания: " << subjects[i].getKnowledge() << "/100 | Посещено пар: " << subjects[i].getAttendance() << " | Сдано лаб: " << subjects[i].getLabsCompleted() << "\n";

        double baseScore = (subjects[i].getKnowledge() / 100.0) * 6.0;
        baseScore += min(1.2, subjects[i].getAttendance() * 0.4);
        baseScore += min(1.0, subjects[i].getLabsCompleted() * 0.5);

        if (student.getEnergy() < 20 || student.getMood() < 20) {
            cout << "Из-за сильной усталости или плохого настроения вы волнуетесь (-0.5 балла).\n";
            baseScore -= 0.5;
        }
        cout << "\nПреподаватель задаёт дополнительный вопрос для повышения оценки:\n";
        cout << "Вопрос: " << subjects[i].getQuestion() << "\n";
        cout << "Ваш ответ: ";
        string userAns;
        getline(cin, userAns);
        if (subjects[i].checkAnswer(userAns)) {
            cout << "Верно! Преподаватель доволен (+2.0 балла).\n";
            baseScore += 2.0;
        }
        else {
            cout << "Не совсем точно. Бонус за ответ не начислен.\n";
        }
        int finalGrade = static_cast<int>(baseScore + 0.5);
        finalGrade = max(1, min(10, finalGrade));
        subjects[i].setExamGrade(finalGrade);
        cout << "Итоговая оценка по предмету \"" << subjects[i].getName() << "\": " << finalGrade << " баллов ";
        if (finalGrade >= 4) {
            cout << "(СДАНО)\n";
            passedCount++;
        }
        else {
            cout << "(ПЕРЕСДАЧА)\n";
        }
        sumGrades += finalGrade;
    }
    cout << "                 ИТОГИ СЕССИИ\n";
    cout << "Студент: " << student.getName() << " (" << student.getSpecialty() << ")\n";
    cout << "Сдано предметов: " << passedCount << " из " << subjects.size() << "\n";
    cout << "Средний балл: " << (sumGrades / subjects.size()) << "\n";
    cout << "Оставшийся бюджет: " << student.getMoney() << " руб.\n";
    if (passedCount == static_cast<int>(subjects.size())) {
        cout << "Поздравляем! Вы успешно закрыли сессию без долгов!\n";
    }
    else if (passedCount >= static_cast<int>(subjects.size()) / 2) {
        cout << "Сессия закрыта с задолженностями. Придётся сходить на пересдачу.\n";
    }
    else {
        cout << "Слишком много долгов! Вы на грани отчисления.\n";
    }
    StopCls();
}

// Основной цикл по дням
void playGameLoop(Student& student, vector<Subject>& subjects, int startDay, int totalDays) {
    Action actAttend("Посетить пару", ActionType::ATTEND_CLASS);
    Action actSkip("Прогулять пару", ActionType::SKIP_CLASS);
    Action actStudy("Учить конспекты дома", ActionType::STUDY_HOME);
    Action actTasks("Решать практические задачи", ActionType::SOLVE_TASKS);
    Action actRest("Отдохнуть и выспаться", ActionType::REST);
    Action actCoffee("Купить кофе и перекус", ActionType::BUY_COFFEE);

    const int MONTH_LENGTH = 5; // Выплата раз в этот срок. Условный месяц, т.к. делать его полным я считаю было бы слишком долго для проверок :)
    const int ATTESTATION_PERIOD = 4; // Каждые 4 дня проводится аттестация

    cin.ignore();
    for (int day = startDay; day <= totalDays; ++day) {
        system("cls");
        cout << "### УЧЕБНЫЙ ДЕНЬ " << day << " ИЗ " << totalDays << " ###\n";

        
        if (day > 1 && (day - 1) % MONTH_LENGTH == 0) { // Ежемесячное начисление денег 
            student.receiveMonthlyAllowance();
        }

        student.printStatus();
        cout << "Успеваемость по предметам:\n";
        for (size_t i = 0; i < subjects.size(); ++i) {
            cout << "  " << (i + 1) << ". " << subjects[i].getName() << " | Знания: " << subjects[i].getKnowledge() << "%, Посещений: " << subjects[i].getAttendance() << ", Лаб: " << subjects[i].getLabsCompleted() << ", Аттестация: " << subjects[i].getMidTermGrade() << "/10 |\n";
        }
        
        int subjIndex = (day - 1) % subjects.size(); // Утро/день
        Subject& todaySubject = subjects[subjIndex];
        cout << "\n| УТРО / УНИВЕРСИТЕТ |\n";
        cout << "Сегодня по расписанию пара: \"" << todaySubject.getName() << "\".\n";
        cout << "1. " << actAttend.getTitle() << " (-15 энергии, -10 руб. на проезд/обед, +знания)\n";
        cout << "2. " << actSkip.getTitle() << " (-30 руб., +15 энергии, +20 настроения)\n";
        cout << "3. Сохранить игру и выйти в меню\n";
        cout << "Выберите действие: ";
        int morningChoice = 0;
        cin >> morningChoice;
        cin.ignore();

        if (morningChoice == 3) {
            saveGameProgress(student, subjects, day, totalDays, "savegame.txt", false);
            StopCls();
            return;
        }
        else if (morningChoice == 2) {
            actSkip.execute(student, &todaySubject);
        }
        else {
            actAttend.execute(student, &todaySubject);

            
            if (day % 2 == 0) { // Лаба по чётным дням при посещении
                cout << "\n| КОНТРОЛЬ ЗНАНИЙ | На паре проводится защита лабораторной работы по предмету \"" << todaySubject.getName() << "\"!\n";
                int labGrade = todaySubject.passLab();
                cout << "Ваша оценка за лабораторную: " << labGrade << "/10. ";
                if (labGrade >= 4) {
                    cout << "Лабораторная зачтена (+5% знаний)!\n";
                }
                else {
                    cout << "Лабораторная НЕ зачтена. Нужно лучше готовиться.\n";
                    student.changeMood(-10);
                }
            }
        }


        cout << "\n| ВЕЧЕР / ДОМА|\n"; // Вечер/дом
        cout << "Чем вы займётесь вечером?\n";
        cout << "1. " << actStudy.getTitle() << " (-20 энергии, +знания)\n";
        cout << "2. " << actTasks.getTitle() << " (-25 энергии, ++знания)\n";
        cout << "3. " << actRest.getTitle() << " (+40 энергии, +25 настроения)\n";
        cout << "4. " << actCoffee.getTitle() << " (-25 руб., +30 энергии, +20 настроения)\n";
        cout << "Выберите действие: ";
        int eveningChoice = 0;
        cin >> eveningChoice;
        cin.ignore();

        if (eveningChoice == 1 || eveningChoice == 2) {
            int targetSubj = 0;
            if (subjects.size() > 1) {
                cout << "Выберите номер предмета для подготовки (1-" << subjects.size() << "): ";
                cin >> targetSubj;
                cin.ignore();
                targetSubj = max(1, min(static_cast<int>(subjects.size()), targetSubj)) - 1;
            }
            if (eveningChoice == 1) {
                actStudy.execute(student, &subjects[targetSubj]);
            }
            else {
                actTasks.execute(student, &subjects[targetSubj]);
            }
        }
        else if (eveningChoice == 4) {
            actCoffee.execute(student);
        }
        else {
            actRest.execute(student);
        }

   
        if (day % ATTESTATION_PERIOD == 0 && day < totalDays) { // Общая аттестация каждое кол-во дней из ATTESTATION_PERIOD
            runMidTermAttestation(student, subjects);
        }

        cout << "\nДень " << day << " завершён.\n";
        saveGameProgress(student, subjects, day + 1, totalDays, "autosave.txt", true);
        system("pause");
    }

    runSession(student, subjects);
}

void startGame(const Settings& s) {
    system("cls");
    srand(static_cast<unsigned int>(time(nullptr))); // Чтобы значения при каждом запуске отличались
    string name = s.studentName.empty() ? "Студент" : s.studentName;
    string spec = s.specialty.empty() ? "ПО" : s.specialty;
    Student student(name, spec);
    vector<Subject> subjects = generateSubjects(s);
    int totalDays = max(8, static_cast<int>(subjects.size()) * 2);
    cout << "Добро пожаловать в Неназванный университет, " << student.getName() << "!\n";
    cout << "Ваша специальность: " << student.getSpecialty() << ".\n";
    cout << "Стартовый бюджет: " << student.getMoney() << " руб. (ежемесячная выплата: " << student.getMonthlyIncome() << " руб.).\n";
    cout << "Количество предметов в семестре: " << subjects.size() << ".\n";
    cout << "До начала сессии осталось учебных дней: " << totalDays << ".\n\n";
    system("pause");
    playGameLoop(student, subjects, 1, totalDays);
}

void loadGame(const Settings& s) {
    ifstream checkManual("savegame.txt"); // Проверка ручного сохранения
    bool hasManual = checkManual.good(); // true если файл существует/доступен
    checkManual.close();
    ifstream checkAuto("autosave.txt"); // Проверка авто сохранения
    bool hasAuto = checkAuto.good();
    checkAuto.close();
    if (!hasManual && !hasAuto) { // Если нет ни того ни другого
        cout << "Сохранения не найдены\n";
        StopCls();
        return;
    }
    cout << "\nВыберите слот для загрузки:\n";
    cout << "1. Обычное сохранение " << (hasManual ? "(доступно)" : "(пусто)") << "\n";
    cout << "2. Автосохранение " << (hasAuto ? "(доступно)" : "(пусто)") << "\n";
    cout << "0. Назад в меню\n";
    cout << "Ваш выбор: ";
    int slotChoice = 0;
    cin >> slotChoice;
    string selectedFile;
    if (slotChoice == 1 && hasManual) {
        selectedFile = "savegame.txt";
    }
    else if (slotChoice == 2 && hasAuto) {
        selectedFile = "autosave.txt";
    }
    else if (slotChoice == 0) {
        system("cls");
        return;
    }
    else {
        cout << "Пусто, либо неверный ввод\n";
        StopCls();
        return;
    }
    Student student;
    vector<Subject> subjects;
    int currentDay = 1, totalDays = 8;
    if (!loadGameFromFile(selectedFile, student, subjects, currentDay, totalDays)) {
        cout << "Ошибка чтения файла сохранения\n";
        StopCls();
        return;
    }
    cout << "Загружено сохранение: " << student.getName() << " (День " << currentDay << " из " << totalDays << ").\n";
    system("pause");
    playGameLoop(student, subjects, currentDay, totalDays);
}