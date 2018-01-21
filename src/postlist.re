
/* Create a GraphQL Query by using the graphql_ppx */ 
module PostsQuery = [%graphql {|
    query {
        allPosts {
          id
          title
          body
        }
      }
  |}]; 

  let component = ReasonReact.statelessComponent("Greeting");

  module Query = Client.Instance.Query;
  
  let make = (_children) => {
  ...component,
  render: (_) => {
      let unexpectedError = <div> (ReasonReact.stringToElement("There was an internal error")) </div>;
      let postsQuery = PostsQuery.make(());
      <Query query=postsQuery>
      ((response, parse) => {
        switch response {
           | Loading => <div> (ReasonReact.stringToElement("Loading")) </div>
           | Failed(error) => <div> (ReasonReact.stringToElement(error)) </div>
           | Loaded(result) => {
            let result = parse(result);
             <div>
             (
              ReasonReact.arrayToElement(
                Array.map(((post) => 
                <div key=(post##id)> 
                <p key=(post##id)>(ReasonReact.stringToElement(post##title))</p>
                <div key=(post##id)>(ReasonReact.stringToElement(post##body))</div>
                </div>), 
                result##allPosts)
              )
             )
  
             </div>
           }
      }})
    </Query>
  }
  };
