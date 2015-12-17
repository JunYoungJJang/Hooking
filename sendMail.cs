=== sender ===
hy3kaka5@gmail.com
kakaotalk=

=== receiever ===
be115kaka5@gmail.com
kakaotalk=

=== send mail ===
// (http://hayoungkim.tistory.com/entry/C-send-email-%EC%9D%B4%EB%A9%94%EC%9D%BC-%EC%A0%84%EC%86%A1-%EC%B2%A8%EB%B6%80%ED%8C%8C%EC%9D%BC)

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Mail;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MailMessage mail = new MailMessage();

            mail.From = new MailAddress("be115kaka5@gmail.com");

            mail.To.Add("hy3kaka5@gmail.com");
            mail.Subject = "회원님의 ID/PW가 유출되었습니다.";
            mail.Body = ""
        }
    }
}
