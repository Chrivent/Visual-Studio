using MySql.Data.MySqlClient;

string connectionString = "server=localhost;database=RubiksCode;uid=root;pwd=root;";
MySqlConnection connection = new MySqlConnection(connectionString);
connection.Open();

string sql;
MySqlCommand command;

sql = "UPDATE TwistCode SET user = \"soil\" WHERE id = 2";
command = new MySqlCommand(sql, connection);
command.ExecuteNonQuery();

connection.Close();