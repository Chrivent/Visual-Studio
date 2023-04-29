using MySql.Data.MySqlClient;
using System.Data;
using System.Text;

class NetworkDatabase : IDisposable
{
    MySqlConnection connection;
    public string uid = "root";
    public string password = "root";

    public NetworkDatabase(string database)
    {
        string connectingString = "Server=localhost" + ";Database=" + database + ";Uid=" + uid + ";Pwd=" + password + ";";
        connection = new MySqlConnection(connectingString);

        try
        {
            connection.Open();
            Console.WriteLine("MySQL Connection Successful!");
        }
        catch (MySqlException ex)
        {
            Console.WriteLine("MySQL Connection Failed : " + ex.Message);
        }
    }

    public void UploadQuery(string query)
    {
        MySqlCommand command = new MySqlCommand(query, connection);

        command.ExecuteNonQuery();
    }

    public void Dispose()
    {
        if (connection != null)
        {
            connection.Close();
            Console.WriteLine("MySQL Connection Closed.");
        }
    }
}