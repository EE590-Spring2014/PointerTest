using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using PointerTest.Resources;
using PointerComponent;

namespace PointerTest
{
    public partial class MainPage : PhoneApplicationPage
    {
        public MainPage()
        {
            InitializeComponent();

            // All the interesting stuff is happening in C++, so go check it out!
            PointerExampleInCPP p = new PointerExampleInCPP();
        }
    }
}