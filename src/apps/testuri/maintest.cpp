#include "tstring.hpp"
#include "uri.hpp"
#include "gtest/gtest.h"

using namespace std;

struct URITestFixture : public ::testing::Test {

	razor::IUri * pUri;

	URITestFixture() {
		// initialization code here
	}

	void SetUp(const tstring & strUri) {
		// code here will execute just before the test ensues 
		try {
			pUri = razor::parser::make_uri(strUri);
		}
		catch (razor::baduri_exception) {
		}
	}

	void TearDown() {
		// code here will be called just after the test completes
		// ok to through exceptions from here if need be

		delete pUri;
	}

	virtual ~URITestFixture()  {
		// cleanup any pending stuff, but no exceptions allowed
	}

	// put in any custom data members that you need 
};

struct uri_data {
	tstring Uri;
	tstring Scheme;
	tstring User;
	tstring Password;
	tstring Host;
	tstring Port;
	tstring Path;
	tstring Query;
	tstring Fragment;
	bool IsHostAnIP;
	bool IsEmpty;
	bool IsValid;

	uri_data(const tstring & Uri, const tstring & Scheme, const tstring & User, const tstring & Password, const tstring & Host, const tstring & Port, const tstring & Path, const tstring & Query, const tstring & Fragment, const bool IsHostAnIP, const bool IsEmpty, const bool IsValid)
		:Uri(Uri), Scheme(Scheme), User(User), Password(Password), Host(Host), Port(Port), Path(Path), Query(Query), Fragment(Fragment), IsHostAnIP(IsHostAnIP), IsEmpty(IsEmpty), IsValid(IsValid)
	{
	}

	friend std::ostream& operator<<(std::ostream & os, const uri_data & obj)
	{
		return os << "Uri: " << obj.Uri
			<< ", Scheme: " << obj.Scheme
			<< ", User: " << obj.User
			<< ", Password: " << obj.Password
			<< ", Host: " << obj.Host
			<< ", Port: " << obj.Port
			<< ", Path: " << obj.Path
			<< ", Query: " << obj.Query
			<< ", Fragment: " << obj.Fragment
			<< ", IsHostAnIP: " << obj.IsHostAnIP
			<< ", IsEmpty: " << obj.IsEmpty
			<< ", IsValid: " << obj.IsValid;
	}
};

struct URIValuesTest : URITestFixture, testing::WithParamInterface<uri_data>
{
	URIValuesTest()
	{
		SetUp(GetParam().Uri);
	}
};

TEST_P(URIValuesTest, CheckURIInitialisation)
{
	uri_data as = GetParam();
	EXPECT_EQ(as.IsValid, pUri->IsValid());
	EXPECT_EQ(as.IsHostAnIP, pUri->IsHostAnIP());
	EXPECT_EQ(as.IsEmpty, pUri->IsEmpty());
	EXPECT_EQ(as.Uri, pUri->Scheme());
	EXPECT_EQ(as.User, pUri->User());
	EXPECT_EQ(as.Password, pUri->Password());
	EXPECT_EQ(as.Host, pUri->Host());
	EXPECT_EQ(as.Port, pUri->Port());
	EXPECT_EQ(as.Path, pUri->Path());
	EXPECT_EQ(as.Query, pUri->Query());
	EXPECT_EQ(as.Fragment, pUri->Fragment());
}

TEST(tstringtest, comparevalues) {
	tstring stest;
	stest.append(_T("Ready for kick off.."));
	EXPECT_EQ(stest, _T("Ready for kick off.."));
}

INSTANTIATE_TEST_CASE_P(Default, URIValuesTest,
	testing::Values(
	uri_data("http://localhost:80/homepage.htm?query=value/#fragment", "http", "", "", "localhost", "", "/homepage.htm", "?query=value", "fragment", false, false, true),
	uri_data("http://localhost:80/homepage.htm?query=value/#fragment", "ftp", "", "", "localhost", "", "/clusterfile", "?query=value", "fragment", false, false, true)
));

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	int iresult = RUN_ALL_TESTS();
	getchar();
	return iresult;
}