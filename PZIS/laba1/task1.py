import os
import subprocess
import sys

def execute_command(command):
    try:
        subprocess.run(command, shell=True, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Ошибка при выполнении команды: {e}")

def create_group():
    group_name = input("Введите название группы: ")
    execute_command(f'sudo groupadd {group_name}')

def create_user():
    user_name = input("Введите имя пользователя: ")
    password = input("Введите пароль для пользователя: ")
    group_name = input("Введите название группы (оставьте пустым, если не нужно добавлять в группу): ")
    try:
        if group_name:
            subprocess.run(['sudo', 'useradd', '-G', group_name ,user_name], check=True)
        else:
            subprocess.run(['sudo', 'useradd', user_name], check=True)

        subprocess.run(['sudo', 'passwd', user_name], input=f"{password}\n{password}\n", text=True, check=True)

        print(f"Пользователь {user_name} успешно создан с заданным паролем.")
    except subprocess.CalledProcessError as e:
        print(f"Ошибка при создании пользователя: {e}")

def set_admin_privileges():
    user_name = input("Введите имя пользователя для получения админ прав: ")
    execute_command(f'sudo usermod -aG sudo {user_name}')

def create_directory():
    dir_path = input("Введите название директории: ")
    mode = int(input("Введите права доступа (например, 755): "), 8)
    os.makedirs(dir_path, exist_ok=True)
    os.chmod(dir_path, mode)
    print(f"Директория {dir_path} создана с правами {oct(mode)}.")

def create_file():
    file_path = input("Введите название файлу: ")
    mode = int(input("Введите права доступа к файлу (например, 600): "), 8)
    content = input("Введите содержимое файла: ")
    
    with open(file_path, 'w') as file:
        file.write(content)
    os.chmod(file_path, mode)
    print(f"Файл {file_path} создан с правами {oct(mode)}.")

def switch_user():
    target_user = input("Введите имя пользователя для смены: ")
    try:
        user_info = os.popen(f"id -u {target_user}").read().strip()
        if not user_info:
            print(f"Пользователь {target_user} не найден.")
            return
        
        user_id = int(user_info)

        os.setuid(user_id)
        print(f"Сменен на пользователя: {target_user} (UID: {user_id})")

        print("Теперь программа выполняется от имени другого пользователя.")

    except Exception as e:
        print(f"Ошибка при смене пользователя: {e}")
        sys.exit(1)
    
def add_user_to_group():
    user_name = input("Введите имя пользователя: ")
    group_name = input("Введите название группы: ")
    execute_command(f'sudo usermod -aG {group_name} {user_name}')
    
def check_permissions():
    path = input("Введите путь к файлу или папке для проверки прав: ")
    if os.path.exists(path):
        file_stats = os.stat(path)
        permissions = {
            'readable': os.access(path, os.R_OK),
            'writable': os.access(path, os.W_OK),
            'executable': os.access(path, os.X_OK)
        }
        
        print(f"Права доступа для '{path}':")
        print(f"Чтение: {'Доступно' if permissions['readable'] else 'Недоступно'}")
        print(f"Запись: {'Доступно' if permissions['writable'] else 'Недоступно'}")
        print(f"Выполнение: {'Доступно' if permissions['executable'] else 'Недоступно'}")
    else:
        print(f"Файл или папка '{path}' не существует.")
        
def list_users():
    print("\nСписок всех пользователей:")
    execute_command('getent passwd')

def list_groups():
    print("\nСписок всех групп:")
    execute_command('getent group')

def user_groups():
    user_name = input("Введите имя пользователя для проверки групп: ")
    print(f"\nГруппы пользователя {user_name}:")
    execute_command(f'id {user_name}')
    
def delete_file_or_directory():
    path = input("Введите путь к файлу или папке для удаления: ")
    if os.path.exists(path):
        if os.path.isdir(path):
            execute_command(f'rm -rf {path}')
        else:
            execute_command(f'rm {path}')
        print(f"'{path}' был удален.")
    else:
        print(f"'{path}' не существует.")

def run_sh_file():
    file_path = input("Введите путь к .sh файлу для выполнения: ")
    if os.path.exists(file_path):
        execute_command(f'bash {file_path}')
    else:
        print(f"Файл '{file_path}' не существует.")

def main():
    while True:
        green = "\033[32m"
        reset = "\033[0m"
        
        print(f"{green}\nВыберите действие:{reset}")
        print(f"{green}1. Создать группу{reset}")
        print(f"{green}2. Создать пользователя{reset}")
        print(f"{green}3. Назначить админ права{reset}")
        print(f"{green}4. Добавить пользователя в группу{reset}")
        print(f"{green}5. Создать папку{reset}")
        print(f"{green}6. Создать файл{reset}")
        print(f"{green}7. Сменить пользователя{reset}")
        print(f"{green}8. Проверить права на файл/папку{reset}")
        print(f"{green}9. Просмотреть всех пользователей{reset}")
        print(f"{green}10. Просмотреть все группы{reset}")
        print(f"{green}11. Проверить группы пользователя{reset}")
        print(f"{green}12. Удалить файл/папку{reset}")
        print(f"{green}13. Запустить .sh файл{reset}")
        print(f"{green}0. Выйти{reset}\n")
        
        choice = input("Введите номер команды: ")
        
        if choice == '1':
            create_group()
        elif choice == '2':
            create_user()
        elif choice == '3':
            set_admin_privileges()
        elif choice == '4':
            add_user_to_group()
        elif choice == '5':
            create_directory()
        elif choice == '6':
            create_file()
        elif choice == '7':
            switch_user()
        elif choice == '8':
            check_permissions()
        elif choice == '9':
            list_users()
        elif choice == '10':
            list_groups()
        elif choice == '11':
            user_groups()
        elif choice == '12':
            delete_file_or_directory()
        elif choice == '13':
            run_sh_file()
        elif choice == '0':
            print("Выход из программы.")
            break
        else:
            print("Неверная команда, попробуйте снова.")

if __name__ == "__main__":
    main()