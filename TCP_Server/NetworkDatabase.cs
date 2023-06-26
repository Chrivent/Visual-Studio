using MySql.Data.MySqlClient;
using System;
using System.Data;
using System.Diagnostics;
using System.Text;

class NetworkDatabase : IDisposable
{
    MySqlConnection connection;
    public string uid = "root";
    public string password = "root";
    public bool connect = false;

    public NetworkDatabase(string database)
    {
        string connectingString = "Server=localhost" + ";Database=" + database + ";Uid=" + uid + ";Pwd=" + password + ";";
        connection = new MySqlConnection(connectingString);

        try
        {
            connection.Open();
            connect = true;
            Console.WriteLine("MySQL Connection Successful!");
        }
        catch (MySqlException ex)
        {
            Console.WriteLine("MySQL Connection Failed : " + ex.Message);
        }
    }

    public void SendQuery(string query)
    {
        try
        {
            MySqlCommand command = new MySqlCommand(query, connection);
            command.ExecuteNonQuery();
        }
        catch (MySqlException ex)
        {
            Console.WriteLine("MySQL Error : " + ex.Number + " - " + ex.Message);
        }
    }

    public string ReceiveQuery(string query)
    {
        string data = "";

        try
        {
            MySqlCommand command = new MySqlCommand(query, connection);
            MySqlDataReader reader = command.ExecuteReader();

            while (reader.Read())
            {
                for (int i = 0; i < reader.FieldCount; i++)
                    data += reader[i].ToString() + "|";
                data = data.Substring(0, data.Length - 1);
                data += "_";
            }

            reader.Close();
        }
        catch (MySqlException ex)
        {
            Console.WriteLine("MySQL Error : " + ex.Number + " - " + ex.Message);
        }

        return data!.Substring(0, data.Length - 1);
    }

    public void Dispose()
    {
        if (connection != null)
        {
            connection.Close();
            connect = false;
            Console.WriteLine("MySQL Connection Closed.");
        }
    }
}