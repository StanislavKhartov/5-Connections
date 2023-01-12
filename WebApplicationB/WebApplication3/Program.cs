using Microsoft.AspNetCore.Http.HttpResults;
using Microsoft.AspNetCore.Mvc;

var builder = WebApplication.CreateBuilder(args);

var app = builder.Build();


app.MapGet("/setmessage", (string message) =>
{
    Console.WriteLine($"received message: {message}");
}
);

void callMenu()
{
    Console.WriteLine("1 - Send message\n");
    Console.WriteLine("0 - Exit\n");
}
var client = new HttpClient();


var appRun = app.RunAsync();
await MainLoop();

async Task MainLoop()
{
    int state = 1;
    while (state != 0)
    {
        callMenu();
        state = Convert.ToInt16(Console.ReadLine());
        if (state > 2 || state < 0)
        {
            Console.WriteLine("Wrong state");
            return;
        }
        if (state == 1)
        {
            string message = Console.ReadLine();
            var content = new StringContent(message);
            await client.GetAsync("https://localhost:7258/setmessage?message=" + message);
        }
    }
}