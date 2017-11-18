/*
* This function is written to get token from European Patent Office server 
* 
*
*/
<?php
	function getToken()
	{	
		/* OPS versiyon number.*/
		$base_uri           = 'https://ops.epo.org/3.2/';
		/*
		Consumer Key And Secret Key are  special for the application
		*/
		$consumerKey        = 'your Consumer Key';
		$consumerSecretKey  = 'Your Secret Key';

		/*  The Authorized Key is 'based64 Decoding format' */
		$authorization = 'Authorization: Basic '.'The Authorized Key';
		/* OPS token Server*/
		$url = 'https://ops.epo.org/3.2/auth/accesstoken';


		/* The response from OPS server. Basically it also contains the token*/
		$tkn =  curl_init();
		curl_setopt($tkn, CURLOPT_URL, $url);
		curl_setopt($tkn, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($tkn, CURLOPT_POSTFIELDS, 'grant_type=client_credentials');
		curl_setopt($tkn, CURLOPT_HTTPHEADER,[
			'authorization'     => $authorization,
			'content-type'      => 'application/x-www-form-urlencoded',
			'grant_type'        => 'client_credentials'
		]);
		curl_setopt($tkn, CURLOPT_POST,true);
		$ops_token_response = curl_exec($tkn);
		curl_close($tkn);

		/* The response is in JSon format. So supposed to decode to get the token*/
		$ops_token_response = json_decode($ops_token_response,true);
	
		return  $ops_token_response['access_token'];;
		
	}