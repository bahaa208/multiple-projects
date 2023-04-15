using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WpfAppEtest
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    /// 

    /*
     * this is the main window 
     * put user name and password to get in 
     * username and pass should be not empty
     * got error massege if the are empty
     * radio button check if the client is student or teacher 
     * and open the student window if student else teacher window
     * */
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }
        // login button function
        private void LoginButton_Click(object sender, RoutedEventArgs e)
        {
            string username = UsernameTextBox.Text;
            string password = PasswordTextBox.Password;
            bool canOpen = false;
            if (username != "" && password != "")
            {
                ErrorTextBlock.Text = "yes ";
                canOpen = true;
            }
             

            // Perform student login action
            if (LoginS.IsChecked == true)
            {
                if(canOpen)
                {// open student window
                    StudentWindow win2 = new StudentWindow();
                    win2.Show();
                }
                else
                {
                    ErrorTextBlock.Text = "Empty username or password";
                }
                
            }
            // Perform teacher login action
            else if (LoginT.IsChecked == true)
            {
                
                
                if (canOpen)
                {// open teacher window 
                    TeacherWindow win2 = new TeacherWindow();
                    win2.Show();
                }
                else
                {
                    ErrorTextBlock.Text = "Empty username or password";
                }
            }
            else
            {
                ErrorTextBlock.Text = "Please select a login option";
            }
        }

    }
}
