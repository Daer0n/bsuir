import subprocess

# Function to install the database
def install(option):
    if option == "postgresql":
        try:
            result = subprocess.run(
                ["sudo", "apt-get", "install", "postgresql"],
                check=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE
            )
            print(f"Установлено: {result.stdout.decode()}")
        except subprocess.CalledProcessError as e:
            print(f"Ошибка установки: {e.stderr.decode()}")
    else:
        print("Недоступный вариант")

# Function to configure access
def configure_access(db_name, user):
    try:
        result = subprocess.run(
            ["sudo", "-u", "postgres", "psql", "-c", f"CREATE USER {user} WITH PASSWORD 'password';"],
            check=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )
        print(f"Пользователь {user} создан.")
    except subprocess.CalledProcessError as e:
        print(f"Ошибка настройки доступа: {e.stderr.decode()}")

# Function to check security policy
def check_security_policy():
    try:
        result = subprocess.run(
            ["sudo", "-u", "postgres", "psql", "-c", "\\du"],
            check=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )
        print(f"Политики безопасности: {result.stdout.decode()}")
    except subprocess.CalledProcessError as e:
        print(f"Ошибка проверки политики: {e.stderr.decode()}")

# Function to uninstall the database
def uninstall(option):
    if option == "postgresql":
        try:
            result = subprocess.run(
                ["sudo", "apt-get", "remove", "--purge", "postgresql"],
                check=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE
            )
            print(f"Удалено: {result.stdout.decode()}")
        except subprocess.CalledProcessError as e:
            print(f"Ошибка удаления: {e.stderr.decode()}")
    else:
        print("Недоступный вариант")

# Main menu loop
def main_menu():
    while True:
        print("1. Установить PostgreSQL")
        print("2. Настроить доступ")
        print("3. Проверить политику безопасности")
        print("4. Удалить PostgreSQL")
        print("5. Выйти")
        
        choice = input("Введите номер команды: ")

        if choice == "1":
            install("postgresql")
        elif choice == "2":
            db_name = input("Введите имя базы данных: ")
            user = input("Введите имя пользователя: ")
            configure_access(db_name, user)
        elif choice == "3":
            check_security_policy()
        elif choice == "4":
            uninstall("postgresql")
        elif choice == "5":
            print("Выход из программы.")
            break
        else:
            print("Некорректный ввод, попробуйте снова.")

# Run the menu
if __name__ == "__main__":
    main_menu()