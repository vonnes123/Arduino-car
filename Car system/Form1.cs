using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace Car_system
{
    public partial class Form1 : Form
    {
        private SerialPort port4;

        int counter = 1;
        public Form1()
        {
            InitializeComponent();
            start();
        }
        private void start ()
        {
            //we setup the port
            port4 = new SerialPort();
            port4.BaudRate = 9600;
            port4.PortName = "COM4";
            port4.Open();
            tbxHeadlight.Text = "OFF";

        }
        private void Form1_FormClosed(object sender, FormClosedEventArgs e) 
        {
            //closing the port connection when the form is clossed
            port4.Close(); 
        }

        private void bAlarm_Click(object sender, EventArgs e)
        {
            //we have a counter to see if the alarm button is clicked 
            if (counter == 1)
            {
                //the alarm is on
                port4.WriteLine("H");
                lbxLog.Items.Add("Alarm ON");
                counter++;
            }
            else {
                //the alarm is off
                port4.WriteLine("N");
                lbxLog.Items.Add("Alarm OFF");
                counter = 1;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            //we read the inforamtion from the arduino
            if (port4.BytesToRead > 0)
            {
                string text = port4.ReadLine();
                text = text.Trim();

                switch (text.Substring(0, 1))
                {
                    //we read the temperature
                    case "T":
                        text = text.Substring(1);
                        tbxTemperature.Text = text + " C";
                        break;
                        //we read the headlights
                    case "H":
                        text = text.Substring(1);
                        tbxHeadlight.Text = text.ToUpper();
                        lbxLog.Items.Add("Headlights " + text);
                        break;
                    case "M":
                        //we read the movement of the car
                        text = text.Substring(1);
                        text = "Turn " + text;
                        lbxLog.Items.Add(text);
                        break;
                    case "L":
                        //we read the movement of the car
                        text = text.Substring(1);
                        lbxLog.Items.Add(text);
                        break;
                }
                //we autoscroll the log
                lbxLog.SelectedIndex = lbxLog.Items.Count -1;
            }
        }
    }
}
