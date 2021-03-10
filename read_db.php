<!DOCTYPE html>
<html>
	<head>
		<style>
			table {
				border-collapse: collapse;
				width: 100%;
				color: #1f5380;
				font-family: monospace;
				font-size: 20px;
				text-align: left;
			} 
			th {
				background-color: #1f5380;
				color: white;
			}
			tr:nth-child(even) {background-color: #f2f2f2}
		</style>
	</head>
	<?php
		//Creates new record as per request
		//Connect to database
		$hostname = "localhost";		//example = localhost or 192.168.0.0
		$username = "root";		//example = root
		$password = "";	
		$dbname = "pzemsensor";
		// Create connection
		$conn = mysqli_connect($hostname, $username, $password, $dbname);
		// Check connection
		if (!$conn) {
			die("Connection failed !!!");
		} 
	?>
	<body>
		<table>
			<tr>
				<th>No</th> 
				<th>Time</th> 
				<th>Voltage</th>
				<th>Current</th>
				<th>Power</th>
				<th>Energy</th>
				<th>Frequency</th>
				<th>PF</th>
			</tr>	
			<?php
				$table = mysqli_query($conn, "SELECT No, Time, Voltage, Current, Power, Energy, Frequency, PF FROM pzemtable"); //nodemcu_ldr_table = Youre_table_name
				while($row = mysqli_fetch_array($table))
				{
			?>
			<tr>
				<td><?php echo $row["No"]; ?></td>
				<td><?php echo $row["Time"]; ?></td>
				<td><?php echo $row["Voltage"]; ?></td>
				<td><?php echo $row["Current"]; ?></td>
				<td><?php echo $row["Power"]; ?></td>
				<td><?php echo $row["Frequency"]; ?></td>
				<td><?php echo $row["PF"]; ?></td>
			</tr>
			<?php
				}
			?>
		</table>
	</body>
</html>